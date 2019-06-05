// Distributed under the BSD 2-Clause License - Copyright 2012-2019 Robin Degen

#pragma once

#include <aeon/sockets/http/status_code.h>
#include <aeon/streams/devices/memory_device.h>
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
    streams::memory_device<std::vector<char>> content_;
};

} // namespace aeon::sockets::http
