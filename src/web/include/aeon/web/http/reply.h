// Distributed under the BSD 2-Clause License - Copyright 2012-2020 Robin Degen

#pragma once

#include <aeon/web/http/status_code.h>
#include <aeon/streams/devices/memory_device.h>
#include <string>
#include <vector>
#include <map>

namespace aeon::web::http
{

class reply
{
    friend class http_client_socket;

public:
    reply();
    explicit reply(const status_code status);

    [[nodiscard]] auto get_status_code() const
    {
        return status_;
    }

    [[nodiscard]] auto get_content_length() const
    {
        return content_.size();
    }

    [[nodiscard]] auto get_content() -> std::vector<std::uint8_t>;

    [[nodiscard]] auto get_raw_headers() const -> const std::vector<std::string> &;

private:
    void append_raw_http_header_line(const std::string &header_line);
    void append_raw_content_data(const std::vector<std::uint8_t> &data);

    status_code status_;
    std::vector<std::string> raw_headers_;
    streams::memory_device<std::vector<char>> content_;
};

} // namespace aeon::web::http
