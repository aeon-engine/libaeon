/*
 * Copyright (c) 2012-2018 Robin Degen
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

#include <string>

namespace aeon::sockets::http
{

class request;
class http_server_socket;
class routable_http_server_session;

class route
{
public:
    explicit route(std::string mount_point);
    virtual ~route() = default;

    route(route &&) = default;
    auto operator=(route &&) -> route & = default;

    route(const route &) = delete;
    auto operator=(const route &) -> route & = delete;

    virtual void on_http_request(http_server_socket &source, routable_http_server_session &session,
                                 const request &request) = 0;

    auto mount_point() const noexcept -> const std::string &;

private:
    std::string mount_point_;
};

inline route::route(std::string mount_point)
    : mount_point_{std::move(mount_point)}
{
}

inline auto route::mount_point() const noexcept -> const std::string &
{
    return mount_point_;
}

} // namespace aeon::sockets::http
