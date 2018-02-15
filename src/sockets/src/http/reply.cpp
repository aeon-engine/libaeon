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

#include <aeon/sockets/http/reply.h>

namespace aeon::sockets::http
{

reply::reply()
    : status_(status_code::internal_server_error)
    , raw_headers_()
    , content_()
{
}

reply::reply(const status_code status)
    : status_(status)
    , raw_headers_()
    , content_()
{
}

auto reply::get_content() -> std::vector<std::uint8_t>
{
    return content_.read_to_vector();
}

auto reply::get_raw_headers() const -> const std::vector<std::string> &
{
    return raw_headers_;
}

void reply::append_raw_http_header_line(const std::string &header_line)
{
    raw_headers_.push_back(header_line);
}

void reply::append_raw_content_data(const std::vector<std::uint8_t> &data)
{
    content_.vector_write(data);
}

} // namespace aeon::sockets::http
