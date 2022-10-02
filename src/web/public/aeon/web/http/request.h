// Distributed under the BSD 2-Clause License - Copyright 2012-2022 Robin Degen

#pragma once

#include <aeon/web/http/method.h>
#include <aeon/streams/devices/memory_device.h>
#include <string>
#include <vector>
#include <map>

namespace aeon::web::http
{

class request
{
    friend class http_server_socket;

public:
    explicit request(const http_method method);
    explicit request(const std::u8string &method, std::u8string uri);

    auto get_method() const noexcept
    {
        return method_;
    }

    auto get_uri() const
    {
        return uri_;
    }

    void set_uri(const std::u8string &uri)
    {
        uri_ = uri;
    }

    auto get_content_length() const
    {
        return content_.size();
    }

    auto has_content() const
    {
        return content_.size() != 0;
    }

    auto get_content() const -> std::vector<std::uint8_t>;

    auto get_content_string() const -> std::u8string;

    auto get_content_type() const -> std::u8string;

    auto get_raw_headers() const -> const std::vector<std::u8string> &;

private:
    void append_raw_http_header_line(const std::u8string &header_line);
    void append_raw_content_data(const std::vector<std::byte> &data) const;
    void set_content_type(const std::u8string &content_type);

    http_method method_;
    std::u8string uri_;
    std::vector<std::u8string> raw_headers_;

    std::u8string content_type_;
    mutable streams::memory_device<std::vector<char>> content_;
};

auto parse_raw_http_headers(const std::vector<std::u8string> &raw_headers) -> std::map<std::u8string, std::u8string>;

} // namespace aeon::web::http
