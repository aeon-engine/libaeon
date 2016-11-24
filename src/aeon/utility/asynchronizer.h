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

class asynchronizer : noncopyable
{
public:
    asynchronizer() = default;
    ~asynchronizer() = default;

    void post(std::function<void()> job)
    {
        std::unique_lock<std::mutex> lock(mutex_);
        queue_.push(job);
    }

    void call(std::function<void()> job)
    {
        std::promise<void> promise;
        std::future<void> future = promise.get_future();

        post([&job, &promise]() {
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

        post([&job, &promise]() {
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

    void reset()
    {
        std::lock_guard<std::mutex> guard(mutex_);
        queue_ = std::queue<std::function<void()>>();
    }

protected:
    void execute_all()
    {
        while (execute_one())
        {
        }
    }

    bool execute_one()
    {
        std::function<void()> func;
        {
            std::lock_guard<std::mutex> guard(mutex_);

            if (queue_.empty())
                return false;

            func = queue_.front();
            queue_.pop();
        }

        func();
        return true;
    }

private:
    std::mutex mutex_;
    std::queue<std::function<void()>> queue_;
};

} // namespace utility
} // namespace aeon
