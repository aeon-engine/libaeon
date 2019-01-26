// Copyright (c) 2012-2019 Robin Degen

#include <aeon/sockets/http/reply.h>

namespace aeon::sockets::http
{

reply::reply()
    : reply{status_code::internal_server_error}
{
}

reply::reply(const status_code status)
    : status_{status}
    , raw_headers_{}
    , content_{}
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
