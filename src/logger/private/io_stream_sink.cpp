// Distributed under the BSD 2-Clause License - Copyright 2012-2023 Robin Degen

#include <aeon/logger/io_stream_sink.h>
#include <aeon/streams/stream_writer.h>

namespace aeon::logger
{

io_stream_sink::io_stream_sink(streams::stdio_device &stream)
    : stream_(stream)
{
}

void io_stream_sink::log(const common::string &message, const common::string &module, const log_level level)
{
    streams::stream_writer writer(stream_);

    // TODO: This should be optimized with a string formatter. Perhaps a stream filter can help.

    stream_.set_color(aeon::streams::color::white);
    writer << '[';

    stream_.set_color(aeon::streams::color::cyan);

    writer << module;

    stream_.set_color(aeon::streams::color::white);

    writer << "] [";

    stream_.set_color(log_level_to_color(level));

    writer << log_level_str[static_cast<int>(level)];

    stream_.set_color(aeon::streams::color::white);

    writer << "]: ";
    writer << message;
    writer << '\n';
}

[[nodiscard]] auto io_stream_sink::log_level_to_color(const log_level level) const -> streams::color
{
    switch (level)
    {
        case log_level::trace:
        case log_level::debug:
            return streams::color::magenta;
        case log_level::message:
            return streams::color::green;
        case log_level::warning:
            return streams::color::yellow;
        case log_level::fatal:
        case log_level::error:
            return streams::color::red;
        default:
            return streams::color::white;
    }
}

} // namespace aeon::logger
