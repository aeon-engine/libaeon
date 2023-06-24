// Distributed under the BSD 2-Clause License - Copyright 2012-2023 Robin Degen

#pragma once

#include <functional>
#include <list>
#include <mutex>
#include <atomic>

namespace aeon::common
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

    signal_connection(signal_connection<Args...> &&other) noexcept
        : handle_(other.handle_)
        , func_(std::move(other.func_))
        , disconnect_(std::move(other.disconnect_))
    {
        other.handle_ = 0;
    }

    ~signal_connection() = default;

    auto operator=(signal_connection<Args...> &&other) noexcept -> signal_connection &
    {
        handle_ = other.handle_;
        func_ = std::move(other.func_);
        disconnect_ = std::move(other.disconnect_);

        other.handle_ = 0;
        return *this;
    }

    signal_connection(const signal_connection<Args...> &) = default;
    auto operator=(const signal_connection<Args...> &) -> signal_connection & = default;

    [[nodiscard]] auto get_handle() const
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
class [[nodiscard]] scoped_signal_connection
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

    scoped_signal_connection(const scoped_signal_connection<Args...> &other) = delete;
    scoped_signal_connection &operator=(const scoped_signal_connection &other) = delete;

    [[nodiscard]] auto get_handle() const
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

    scoped_signal_connection<Args...> connect(signal_func<Args...> f)
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
        for (auto &c : connections_)
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

    scoped_signal_connection<Args...> connect(signal_func<Args...> f)
    {
        int handle = ++last_handle_;
        auto disconnect_func = [this, handle]() { disconnect(handle); };
        auto connection = signal_connection<Args...>(++last_handle_, f, disconnect_func);
        {
            std::lock_guard<mutex_type> guard(lock_);
            connections_.push_back(connection);
        }

        return connection;
    }

    void disconnect(const scoped_signal_connection<Args...> &c)
    {
        disconnect(c.get_handle());
    }

    void disconnect(const int handle)
    {
        std::lock_guard<mutex_type> guard(lock_);
        connections_.remove_if([&handle](const signal_connection<Args...> &other)
                               { return other.get_handle() == handle; });
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

} // namespace aeon::common
