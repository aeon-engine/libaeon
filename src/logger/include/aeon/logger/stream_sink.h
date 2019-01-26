// Copyright (c) 2012-2019 Robin Degen

#pragma once

#include <aeon/logger/log_sink.h>
#include <aeon/logger/log_level.h>
#include <aeon/streams/stream_fwd.h>
#include <string>

namespace aeon::logger
{

class stream_sink : public log_sink
{
public:
    explicit stream_sink(streams::stream &stream);
    virtual ~stream_sink() = default;

    stream_sink(const stream_sink &) = delete;
    auto operator=(const stream_sink &) noexcept -> stream_sink & = delete;

    stream_sink(stream_sink &&) = delete;
    auto operator=(stream_sink &&) noexcept -> stream_sink & = delete;

private:
    void log(const std::string &message, const std::string &module, log_level level) override;

    streams::stream &stream_;
};

} // namespace aeon::logger
