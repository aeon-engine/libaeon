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

class simple_sink_backend : public base_backend
{
public:
    simple_sink_backend()
        : base_backend(log_level::message)
    {
    }

    simple_sink_backend(log_level level)
        : base_backend(level)
    {
    }

    simple_sink_backend(const simple_sink_backend &) = delete;

    void add_sink(log_sink_ptr sink)
    {
        sinks_.insert(sink);
    }

    void remove_all_sinks()
    {
        sinks_.clear();
    }

private:
    virtual void log(std::string &&message, log_level level)
    {
        for (auto &sink : sinks_)
        {
            sink->log(message, level);
        }
    }

    std::set<log_sink_ptr> sinks_;
};

} // namespace logger
} // namespace aeon
