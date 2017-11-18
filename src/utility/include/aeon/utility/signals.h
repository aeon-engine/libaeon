/*
 * Copyright (c) 2012-2017 Robin Degen
 *
 * Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this software and associated documentation
 * files (the "Software"), to deal in the Software without
 * restriction, including without limitation the rights to use,
 * copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following
 * conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
 * OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
 * HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 * WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 */

#pragma once

#include <aeon/common/noncopyable.h>
#include <functional>
#include <list>
#include <mutex>
#include <atomic>

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
        , func_()
        , disconnect_()
    {
    }

    explicit signal_connection(int handle, signal_func<Args...> func, std::function<void()> disconnect)
        : handle_(handle)
        , func_(func)
        , disconnect_(disconnect)
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

    void disconnect()
    {
        if (disconnect_)
            disconnect_();

        handle_ = 0;
    }

    explicit operator bool() const
    {
        return handle_ != 0;
    }

private:
    int handle_;
    signal_func<Args...> func_;
    std::function<void()> disconnect_;
};

template <class... Args>
class scoped_signal_connection : common::noncopyable
{
public:
    scoped_signal_connection()
        : signal_()
    {
    }

    scoped_signal_connection(signal_connection<Args...> &&signal)
        : signal_(std::move(signal))
    {
    }

    ~scoped_signal_connection()
    {
        if (signal_)
            signal_.disconnect();
    }

    scoped_signal_connection(scoped_signal_connection<Args...> &&other)
        : signal_(std::move(other.signal_))
    {
    }

    scoped_signal_connection &operator=(scoped_signal_connection &&other)
    {
        signal_ = std::move(other.signal_);
        return *this;
    }

    int get_handle() const
    {
        return signal_.get_handle();
    }

    void emit(Args... args)
    {
        signal_.emit(args...);
    }

    void disconnect() const
    {
        signal_.disconnect();
    }

private:
    signal_connection<Args...> signal_;
};

template <class... Args>
class signal
{
public:
    signal()
        : last_handle_(0)
        , connections_()
    {
    }

    ~signal() = default;

    [[nodiscard]] scoped_signal_connection<Args...> connect(signal_func<Args...> f)
    {
        auto handle = ++last_handle_;
        auto disconnect_func = [this, handle]() { disconnect(handle); };
        auto connection = signal_connection<Args...>(handle, f, disconnect_func);
        connections_.push_back(connection);
        return connection;
    }

    void disconnect(const scoped_signal_connection<Args...> &c)
    {
        disconnect(c.get_handle());
    }

    void disconnect(const int c)
    {
        connections_.remove_if([c](const signal_connection<Args...> &other) { return other.get_handle() == c; });
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

    [[nodiscard]] scoped_signal_connection<Args...> connect(signal_func<Args...> f)
    {
        auto handle = ++last_handle_;
        auto disconnect_func = [this, handle]() { disconnect(handle); };
        auto connection = signal_connection<Args...>(++last_handle_, f, disconnect_func);
        {
            std::lock_guard<mutex_type> guard(lock_);
            connections_.emplace_back(connection);
        }

        return connection;
    }

    void disconnect(const scoped_signal_connection<Args...> &c)
    {
        disconnect(c.get_handle());
    }

    void disconnect(const handle_type handle)
    {
        std::lock_guard<mutex_type> guard(lock_);
        connections_.remove_if(
            [&handle](const signal_connection<Args...> &other) { return other.get_handle() == handle; });
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
