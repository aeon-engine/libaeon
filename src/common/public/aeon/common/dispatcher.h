// Distributed under the BSD 2-Clause License - Copyright 2012-2021 Robin Degen

#pragma once

#include <functional>
#include <mutex>
#include <future>
#include <queue>
#include <atomic>

namespace aeon::common
{

/*!
 * Determines how the dispatcher should stop. Either by calling stop manually (manual_stop) or automaticly
 * when the queue is determined to be empty. Be sure all jobs are queued before calling run when using this mode to
 * prevent race conditions.
 */
enum dispatcher_stop_mode
{
    manual_stop,
    stop_on_empty_queue
};

class dispatcher
{
public:
    static const int signal_wait_timeout_ms = 100;

    explicit dispatcher(dispatcher_stop_mode stop_mode = dispatcher_stop_mode::manual_stop)
        : running_{false}
        , stop_mode_{stop_mode}
    {
    }

    ~dispatcher() = default;

    dispatcher(const dispatcher &) noexcept = delete;
    auto operator=(const dispatcher &) noexcept -> dispatcher & = delete;
    dispatcher(dispatcher &&) noexcept = delete;
    auto operator=(dispatcher &&) noexcept -> dispatcher & = delete;

    void run_one()
    {
        std::function<void()> func;
        {
            std::unique_lock lock(mutex_);
            signal_cv_.wait(lock, [this]() { return !queue_.empty() || !running_; });

            if (!queue_.empty())
            {
                func = std::move(queue_.front());
                queue_.pop();
            }

            if (stop_mode_ == dispatcher_stop_mode::stop_on_empty_queue)
            {
                if (queue_.empty())
                    running_ = false;
            }
        }

        if (func)
            func();
    }

    void run()
    {
        running_ = true;

        while (running_)
        {
            run_one();
        }
    }

    void post(std::function<void()> &&job)
    {
        std::scoped_lock lock(mutex_);
        queue_.push(std::move(job));
        signal_cv_.notify_one();
    }

    void call(std::function<void()> &&job)
    {
        std::promise<void> promise;
        auto future = promise.get_future();

        post(
            [job = std::move(job), &promise]()
            {
                try
                {
                    job();
                    promise.set_value();
                }
                catch (...)
                {
                    promise.set_exception(std::current_exception());
                }
            });

        return future.get();
    }

    template <typename T, std::enable_if_t<!std::is_void_v<T>> * = nullptr>
    T call(std::function<T()> &&job)
    {
        std::promise<T> promise;
        auto future = promise.get_future();

        post(
            [job = std::move(job), &promise]()
            {
                try
                {
                    promise.set_value(job());
                }
                catch (...)
                {
                    promise.set_exception(std::current_exception());
                }
            });

        return future.get();
    }

    void sync_fence()
    {
        std::promise<void> promise;
        auto future = promise.get_future();
        post([&promise]() { promise.set_value(); });
        future.get();
    }

    void stop()
    {
        std::scoped_lock guard(mutex_);
        running_ = false;
        signal_cv_.notify_all();
    }

    void reset()
    {
        std::scoped_lock guard(mutex_);
        queue_ = std::queue<std::function<void()>>();
    }

private:
    std::mutex mutex_;
    std::condition_variable signal_cv_;
    std::queue<std::function<void()>> queue_;
    std::atomic<bool> running_;
    dispatcher_stop_mode stop_mode_;
};

} // namespace aeon::common
