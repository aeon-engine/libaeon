// Copyright (c) 2012-2019 Robin Degen

#include <aeon/logger/io_stream_sink.h>
#include <aeon/streams/stream_writer.h>
#include <aeon/streams/io_stream.h>
#include <aeon/streams/stream_string_operators.h>

namespace aeon::logger
{

io_stream_sink::io_stream_sink(streams::io_stream &stream)
    : stream_(stream)
{
}

void io_stream_sink::log(const std::string &message, const std::string &module, log_level level)
{
    streams::stream_writer writer(stream_);

    stream_.set_color(aeon::streams::color::white);
    stream_.write(reinterpret_cast<const std::uint8_t *>("["), 1);

    stream_.set_color(aeon::streams::color::cyan);

    writer << module;

    stream_.set_color(aeon::streams::color::white);

    stream_.write(reinterpret_cast<const std::uint8_t *>("] ["), 3);

    stream_.set_color(log_level_to_color_(level));

    const auto log_level_string = log_level_str[static_cast<int>(level)];
    writer << log_level_string;

    stream_.set_color(aeon::streams::color::white);

    stream_.write(reinterpret_cast<const std::uint8_t *>("]: "), 3);

    writer.write_line(message);
}

auto io_stream_sink::log_level_to_color_(log_level level) const -> streams::color
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
