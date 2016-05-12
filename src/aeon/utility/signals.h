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

template<class... Args>
using signal_func = std::function<void(Args...)>;

template<class... Args>
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

    void emit(Args...args)
    {
        func_(args...);
    }

private:
    int handle_;
    signal_func<Args...> func_;
};

template<class... Args>
class signal
{
public:
    signal()
        : last_handle_(0)
    {
    }

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
        connections_.remove_if([&c](const signal_connection<Args...> &other) { return other.get_handle() == c.get_handle(); });
    }

    void operator()(Args...args)
    {
        for (auto c : connections_)
        {
            c.emit(args...);
        }
    }

private:
    int last_handle_;
    std::list<signal_connection<Args...>> connections_;
};

} // namespace utility
} // namespace aeon
