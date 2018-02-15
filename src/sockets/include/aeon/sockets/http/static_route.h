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

#include <aeon/sockets/http/route.h>
#include <aeon/common/stdfilesystem.h>
#include <string>
#include <vector>

namespace aeon::sockets::http
{

namespace detail
{
auto to_url_path(const std::string &path) -> std::string;
}

class static_route : public route
{
public:
    explicit static_route(const std::string &mount_point, const std::filesystem::path &base_path);
    explicit static_route(const std::string &mount_point, const std::filesystem::path &base_path,
                          const std::vector<std::string> &default_files);
    virtual ~static_route() = default;

private:
    void on_http_request(http_server_socket &source, http_server_session &session, const request &request) override;

    std::filesystem::path base_path_;
    std::vector<std::string> default_files_;
};

} // namespace aeon::sockets::http
