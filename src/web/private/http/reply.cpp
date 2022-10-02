// Distributed under the BSD 2-Clause License - Copyright 2012-2022 Robin Degen

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

auto reply::get_content() -> std::vector<std::byte>
{
    streams::stream_reader reader{content_};
    std::vector<std::byte> vec;
    reader.read_to_vector(vec);
    return vec;
}

auto reply::get_raw_headers() const -> const std::vector<std::u8string> &
{
    return raw_headers_;
}

void reply::append_raw_http_header_line(const std::u8string &header_line)
{
    raw_headers_.push_back(header_line);
}

void reply::append_raw_content_data(const std::vector<std::byte> &data)
{
    streams::stream_writer writer{content_};
    writer.vector_write(data);
}

} // namespace aeon::web::http
