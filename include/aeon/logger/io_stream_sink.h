/*
 * ROBIN DEGEN; CONFIDENTIAL
 *
 * 2012 - 2016 Robin Degen
 * All Rights Reserved.
 *
 * NOTICE:  All information contained herein is, and remains the property of
 * Robin Degen and its suppliers, if any. The intellectual and technical
 * concepts contained herein are proprietary to Robin Degen and its suppliers
 * and may be covered by U.S. and Foreign Patents, patents in process, and are
 * protected by trade secret or copyright law. Dissemination of this
 * information or reproduction of this material is strictly forbidden unless
 * prior written permission is obtained from Robin Degen.
 */

#pragma once

namespace aeon
{
namespace logger
{

class io_stream_sink : public log_sink
{
public:
    io_stream_sink(aeon::streams::io_stream &stream)
        : stream_(stream)
    {
    }

    virtual ~io_stream_sink() = default;

private:
    void log(const std::string &message, const std::string &module, log_level level) override
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

    streams::color log_level_to_color_(log_level level) const
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

    streams::io_stream &stream_;
};

} // namespace logger
} // namespace aeon
