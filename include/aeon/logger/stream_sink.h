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

class stream_sink : public log_sink
{
public:
    stream_sink(aeon::streams::stream_ptr stream)
        : stream_(stream)
    {
    }

private:
    virtual void log(const std::string &message, aeon::logger::log_level level)
    {
        aeon::streams::stream_writer writer(*stream_);

        stream_->write((const std::uint8_t *)"[", 1);

        std::string log_level_string = aeon::logger::log_level_str[static_cast<int>(level)];
        writer << log_level_string;

        stream_->write((const std::uint8_t *)"]: ", 3);

        writer.write_line(message);
    }

    aeon::streams::stream_ptr stream_;
};

} // namespace logger
} // namespace aeon
