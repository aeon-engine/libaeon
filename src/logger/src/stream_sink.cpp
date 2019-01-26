// Copyright (c) 2012-2019 Robin Degen

#include <aeon/logger/stream_sink.h>
#include <aeon/streams/stream.h>
#include <aeon/streams/stream_writer.h>
#include <aeon/streams/stream_string_operators.h>

namespace aeon::logger
{

stream_sink::stream_sink(streams::stream &stream)
    : stream_(stream)
{
}

void stream_sink::log(const std::string &message, const std::string &module, log_level level)
{
    streams::stream_writer writer(stream_);

    stream_.write(reinterpret_cast<const std::uint8_t *>("["), 1);

    writer << module;

    stream_.write(reinterpret_cast<const std::uint8_t *>("] ["), 3);

    const std::string log_level_string = log_level_str[static_cast<int>(level)];
    writer << log_level_string;

    stream_.write(reinterpret_cast<const std::uint8_t *>("]: "), 3);

    writer.write_line(message);
}

} // namespace aeon::logger
