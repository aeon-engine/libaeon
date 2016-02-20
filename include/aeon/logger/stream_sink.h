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
    stream_sink(streams::stream &stream)
        : stream_(stream)
    {
    }

private:
    void log(const std::string &message, const std::string &module, log_level level) override
    {
        streams::stream_writer writer(stream_);

        stream_.write((const std::uint8_t *)"[", 1);

        writer << module;

        stream_.write((const std::uint8_t *)"] [", 3);

        std::string log_level_string = log_level_str[static_cast<int>(level)];
        writer << log_level_string;

        stream_.write((const std::uint8_t *)"]: ", 3);

        writer.write_line(message);
    }

    streams::stream &stream_;
};

} // namespace logger
} // namespace aeon
