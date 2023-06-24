// Distributed under the BSD 2-Clause License - Copyright 2012-2023 Robin Degen

#pragma once

#include <aeon/logger/log_sink.h>
#include <aeon/logger/log_level.h>
#include <aeon/streams/idynamic_stream.h>

namespace aeon::logger
{

class stream_sink : public log_sink
{
public:
    explicit stream_sink(streams::idynamic_stream &stream);
    ~stream_sink() override = default;

    stream_sink(const stream_sink &) = delete;
    auto operator=(const stream_sink &) noexcept -> stream_sink & = delete;

    stream_sink(stream_sink &&) = delete;
    auto operator=(stream_sink &&) noexcept -> stream_sink & = delete;

private:
    void log(const common::string &message, const common::string &module, const log_level level) override;

    streams::idynamic_stream &stream_;
};

} // namespace aeon::logger
