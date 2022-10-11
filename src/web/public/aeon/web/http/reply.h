// Distributed under the BSD 2-Clause License - Copyright 2012-2022 Robin Degen

#pragma once

#include <aeon/web/http/status_code.h>
#include <aeon/streams/devices/memory_device.h>
#include <aeon/common/string.h>
#include <vector>

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

    [[nodiscard]] auto get_content() -> std::vector<std::byte>;

    [[nodiscard]] auto get_raw_headers() const -> const std::vector<common::string> &;

private:
    void append_raw_http_header_line(const common::string &header_line);
    void append_raw_content_data(const std::vector<std::byte> &data);

    status_code status_;
    std::vector<common::string> raw_headers_;
    streams::memory_device<std::vector<std::byte>> content_;
};

} // namespace aeon::web::http
