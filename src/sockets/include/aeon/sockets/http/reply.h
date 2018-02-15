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

#include <aeon/sockets/http/status_code.h>
#include <aeon/streams/memory_stream.h>
#include <string>
#include <vector>
#include <map>

namespace aeon::sockets::http
{

class reply
{
    friend class http_client_socket;

public:
    reply();
    explicit reply(const status_code status);

    auto get_status_code() const
    {
        return status_;
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

    status_code status_;
    std::vector<std::string> raw_headers_;
    streams::memory_stream content_;
};

} // namespace aeon::sockets::http
