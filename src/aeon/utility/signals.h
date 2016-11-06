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

template <class... Args>
using signal_func = std::function<void(Args...)>;

template <class... Args>
class signal_connection
{
public:
    signal_connection()
        : handle_(0)
    {
    }

    explicit signal_connection(int handle, signal_func<Args...> func)
        : handle_(handle)
        , func_(func)
    {
    }

    int get_handle() const
    {
        return handle_;
    }

    void emit(Args... args)
    {
        func_(args...);
    }

private:
    int handle_;
    signal_func<Args...> func_;
};

template <class... Args>
class signal
{
public:
    signal() = default;
    ~signal() = default;

    signal_connection<Args...> operator+=(signal_func<Args...> f)
    {
        return connect(f);
    }

    signal_connection<Args...> connect(signal_func<Args...> f)
    {
        auto connection = signal_connection<Args...>(++last_handle_, f);
        connections_.push_back(connection);
        return connection;
    }

    void disconnect(signal_connection<Args...> c)
    {
        connections_.remove_if(
            [&c](const signal_connection<Args...> &other) { return other.get_handle() == c.get_handle(); });
    }

    void operator()(Args... args)
    {
        for (auto c : connections_)
        {
            c.emit(args...);
        }
    }

private:
    int last_handle_ = 0;
    std::list<signal_connection<Args...>> connections_;
};

template <class... Args>
class signal_mt
{
    using mutex_type = std::mutex;
    using handle_type = std::atomic<int>;
    using list_type = std::list<signal_connection<Args...>>;

public:
    signal_mt() = default;
    ~signal_mt()
    {
        /* \note This does not solve the 'destruction' while signal is executing problem.
         * Reasoning:
         * Thread a is the owner (he creates and destroys) and thread b executes the signal multiple times. Then
         * while the signal is being destroyed from thread a, thread b tries to execute the signal. Thread a will
         * acquire the mutex and execute the signal destructor. When the signal is destroyed it will release the
         * mutex and allow thread b to execute the signal that does not exist. Which will result in havoc.
         */
        std::lock_guard<mutex_type> guard(lock_);
        connections_.clear();
    }

    signal_connection<Args...> operator+=(signal_func<Args...> f)
    {
        return connect(f);
    }

    signal_connection<Args...> connect(signal_func<Args...> f)
    {
        auto connection = signal_connection<Args...>(++last_handle_, f);
        {
            std::lock_guard<mutex_type> guard(lock_);
            connections_.emplace_back(connection);
        }

        return connection;
    }

    void disconnect(signal_connection<Args...> c)
    {
        std::lock_guard<mutex_type> guard(lock_);
        connections_.remove_if(
            [&c](const signal_connection<Args...> &other) { return other.get_handle() == c.get_handle(); });
    }

    void operator()(Args... args)
    {
        std::lock_guard<mutex_type> guard(lock_);
        for (auto &c : connections_)
            c.emit(args...);
    }

private:
    handle_type last_handle_{0};
    list_type connections_;
    mutex_type lock_;
};

} // namespace utility
} // namespace aeon
