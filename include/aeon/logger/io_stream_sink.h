/*
 * ROBIN DEGEN; CONFIDENTIAL
 *
 * 2012 - 2015 Robin Degen
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
    io_stream_sink(aeon::streams::io_stream_ptr stream)
        : stream_(stream)
    {
    }

private:
    virtual void log(const std::string &message, aeon::logger::log_level level)
    {
        aeon::streams::stream_writer writer(*stream_);

        stream_->set_color(aeon::streams::color::white);
        stream_->write((const std::uint8_t *)"[", 1);

        stream_->set_color(log_level_to_color_(level));

        std::string log_level_string = aeon::logger::log_level_str[static_cast<int>(level)];
        writer << log_level_string;

        stream_->set_color(aeon::streams::color::white);
        stream_->write((const std::uint8_t *)"]: ", 3);

        writer.write_line(message);
    }

    aeon::streams::color log_level_to_color_(log_level level)
    {
        switch (level)
        {
        case aeon::logger::log_level::trace:
        case aeon::logger::log_level::debug:
            return aeon::streams::color::magenta;
        case aeon::logger::log_level::message:
            return aeon::streams::color::green;
        case aeon::logger::log_level::warning:
            return aeon::streams::color::yellow;
        case aeon::logger::log_level::fatal:
        case aeon::logger::log_level::error:
            return aeon::streams::color::red;
        default:
            return aeon::streams::color::white;
        }
    }

    aeon::streams::io_stream_ptr stream_;
};

} // namespace logger
} // namespace aeon
