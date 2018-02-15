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

#include <aeon/sockets/http/request.h>
#include <aeon/common/string.h>

namespace aeon::sockets::http
{

request::request(const method method)
    : method_(method)
    , uri_()
    , raw_headers_()
    , content_()
{
}

request::request(const std::string &method, const std::string &uri)
    : method_(string_to_method(method))
    , uri_(uri)
    , raw_headers_()
    , content_()
{
}

auto request::get_content() -> std::vector<std::uint8_t>
{
    return content_.read_to_vector();
}

auto request::get_raw_headers() const -> const std::vector<std::string> &
{
    return raw_headers_;
}

void request::append_raw_http_header_line(const std::string &header_line)
{
    raw_headers_.push_back(header_line);
}

void request::append_raw_content_data(const std::vector<std::uint8_t> &data)
{
    content_.vector_write(data);
}

auto stip_uri_prefix(const std::string &uri, const std::string &prefix) -> std::string
{
    const auto last_char = *(--prefix.end());

    auto strip_length = prefix.size();
    if (last_char == '/')
        --strip_length;

    if (strip_length > 0)
        return uri.substr(strip_length);

    return uri;
}

auto parse_raw_http_headers(const std::vector<std::string> &raw_headers) -> std::map<std::string, std::string>
{
    std::map<std::string, std::string> headers;

    for (const auto &header_line : raw_headers)
    {
        const auto header_name_end = header_line.find_first_of(':');

        if (header_name_end == std::string::npos)
            return {};

        if (header_name_end + 2 >= header_line.size())
            return {};

        const auto header_name = common::string::to_lower(header_line.substr(0, header_name_end));
        const auto header_value = header_line.substr(header_name_end + 2);

        headers[header_name] = header_value;
    }

    return headers;
}

} // namespace aeon::sockets::http
