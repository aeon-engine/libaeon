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

#include <aeon/sockets/http/method.h>
#include <aeon/streams/memory_stream.h>
#include <string>
#include <vector>
#include <map>

namespace aeon::sockets::http
{

class request
{
    friend class http_server_protocol;

public:
    explicit request(const method method);
    explicit request(const std::string &method, const std::string &uri);

    auto get_method() const
    {
        return method_;
    }

    auto get_uri() const
    {
        return uri_;
    }

    auto get_content_length() const
    {
        return content_.size();
    }

    auto get_content() -> std::vector<std::uint8_t>;

    auto get_raw_headers() const -> const std::vector<std::string> &;

private:
    void append_raw_http_header_line(const std::string &header_line);
    void append_raw_content_data(const std::vector<std::uint8_t> &data);

    method method_;
    std::string uri_;
    std::vector<std::string> raw_headers_;
    streams::memory_stream content_;
};

auto stip_uri_prefix(const std::string &uri, const std::string &prefix) -> std::string;
auto parse_raw_http_headers(const std::vector<std::string> &raw_headers) -> std::map<std::string, std::string>;

} // namespace aeon::sockets::http
