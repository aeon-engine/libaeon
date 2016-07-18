/*
 * ROBIN DEGEN; CONFIDENTIAL
 *
 * 2012 - 2016 Robin Degen
 * All Rights Reserved.
 *
 * NOTICE:  All information contained herein is, and remains the property of
 * Robin Degen and its suppliers, if any. The intellectual and technical
 * concepts contained herein are proprietary to Robin Degen and its suppliers
 * and may be covered by U.S. and Foreign Patents, patents in process, and are
 * protected by trade secret or copyright law. Dissemination of this
 * information or reproduction of this material is strictly forbidden unless
 * prior written permission is obtained from Robin Degen.
 */

#pragma once

namespace aeon
{
namespace utility
{

class dispatcher : noncopyable
{
public:
    static const int signal_wait_timeout_ms = 100;

    dispatcher()
        : running_(false)
    {
    }

    ~dispatcher() = default;

    void run_one()
    {
        std::function<void()> func;
        {
            std::unique_lock<std::mutex> lock(mutex_);
            signal_cv_.wait(
                lock,
                [this](){ return !queue_.empty() || !running_; }
            );

            if (!queue_.empty())
            {
                func = queue_.front();
                queue_.pop();
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

    void post(std::function<void()> job)
    {
        std::unique_lock<std::mutex> lock(mutex_);
        queue_.push(job);
        signal_cv_.notify_one();
    }

    void call(std::function<void()> job)
    {
        std::promise<void> promise;
        std::future<void> future = promise.get_future();

        post([&job, &promise]()
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

    template <typename T, typename std::enable_if<!std::is_void<T>::value>::type * = nullptr>
    T call(std::function<T()> job)
    {
        std::promise<T> promise;
        std::future<T> future = promise.get_future();

        post([&job, &promise]()
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

    void stop()
    {
        std::lock_guard<std::mutex> guard(mutex_);
        running_ = false;
        signal_cv_.notify_all();
    }

    void reset()
    {
        std::lock_guard<std::mutex> guard(mutex_);
        queue_ = std::queue<std::function<void()>>();
    }

private:
    std::mutex mutex_;
    std::condition_variable signal_cv_;
    std::queue<std::function<void()>> queue_;
    bool running_;
};

} // namespace utility
} // namespace aeon
