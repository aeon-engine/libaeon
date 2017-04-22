/*
 * Copyright (c) 2012-2017 Robin Degen
 *
 * Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this software and associated documentation
 * files (the "Software"), to deal in the Software without
 * restriction, including without limitation the rights to use,
 * copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following
 * conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
 * OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
 * HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 * WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 */

#include <aeon/logger/io_stream_sink.h>
#include <aeon/streams/stream_writer.h>
#include <aeon/streams/io_stream.h>

namespace aeon
{
namespace logger
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

    std::string log_level_string = log_level_str[static_cast<int>(level)];
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

} // namespace logger
} // namespace aeon
