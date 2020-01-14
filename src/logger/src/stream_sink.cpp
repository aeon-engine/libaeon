// Distributed under the BSD 2-Clause License - Copyright 2012-2020 Robin Degen

#include <aeon/logger/stream_sink.h>
#include <aeon/streams/stream_writer.h>

namespace aeon::logger
{

stream_sink::stream_sink(streams::idynamic_stream &stream)
    : stream_(stream)
{
}

void stream_sink::log(const std::string &message, const std::string &module, log_level level)
{
    streams::stream_writer writer(stream_);

    writer << '[';
    writer << module;
    writer << "] [";

    const std::string log_level_string = log_level_str[static_cast<int>(level)];
    writer << log_level_string;

    writer << "]: ";

    writer << message;
    writer << '\n';
}

} // namespace aeon::logger
