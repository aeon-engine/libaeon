// Distributed under the BSD 2-Clause License - Copyright 2012-2021 Robin Degen

#include <aeon/web/http/reply.h>
#include <aeon/streams/stream_writer.h>
#include <aeon/streams/stream_reader.h>

namespace aeon::web::http
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
    streams::stream_reader reader{content_};
    std::vector<std::uint8_t> vec;
    reader.read_to_vector(vec);
    return vec;
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
    streams::stream_writer writer{content_};
    writer.vector_write(data);
}

} // namespace aeon::web::http
