// Distributed under the BSD 2-Clause License - Copyright 2012-2022 Robin Degen

#pragma once

#include <aeon/logger/log_sink.h>
#include <aeon/logger/log_level.h>
#include <aeon/streams/devices/stdio_device.h>
#include <aeon/common/string.h>

namespace aeon::logger
{

class io_stream_sink final : public log_sink
{
public:
    explicit io_stream_sink(streams::stdio_device &stream);
    ~io_stream_sink() final = default;

    io_stream_sink(const io_stream_sink &) = delete;
    auto operator=(const io_stream_sink &) noexcept -> io_stream_sink & = delete;

    io_stream_sink(io_stream_sink &&) = delete;
    auto operator=(io_stream_sink &&) noexcept -> io_stream_sink & = delete;

private:
    void log(const common::string &message, const common::string &module, const log_level level) final;
    [[nodiscard]] auto log_level_to_color(const log_level level) const -> streams::color;

    streams::stdio_device &stream_;
};

} // namespace aeon::logger
