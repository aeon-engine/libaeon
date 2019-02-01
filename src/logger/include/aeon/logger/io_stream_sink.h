// Copyright (c) 2012-2019 Robin Degen

#pragma once

#include <aeon/logger/log_sink.h>
#include <aeon/logger/log_level.h>
#include <aeon/streams/devices/stdio_device.h>
#include <string>

namespace aeon::logger
{

class io_stream_sink : public log_sink
{
public:
    explicit io_stream_sink(streams::stdio_device &stream);
    virtual ~io_stream_sink() = default;

    io_stream_sink(const io_stream_sink &) = delete;
    auto operator=(const io_stream_sink &) noexcept -> io_stream_sink & = delete;

    io_stream_sink(io_stream_sink &&) = delete;
    auto operator=(io_stream_sink &&) noexcept -> io_stream_sink & = delete;

private:
    void log(const std::string &message, const std::string &module, log_level level) override;
    auto log_level_to_color_(log_level level) const -> streams::color;

    streams::stdio_device &stream_;
};

} // namespace aeon::logger
