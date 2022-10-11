// Distributed under the BSD 2-Clause License - Copyright 2012-2022 Robin Degen

#include <aeon/logger/simple_sink_backend.h>

namespace aeon::logger
{

simple_sink_backend::simple_sink_backend()
    : base_backend(log_level::message)
{
}

simple_sink_backend::simple_sink_backend(const log_level level)
    : base_backend(level)
{
}

void simple_sink_backend::add_sink(log_sink *sink)
{
    sinks_.insert(sink);
}

void simple_sink_backend::remove_all_sinks()
{
    sinks_.clear();
}

void simple_sink_backend::log(const common::string &message, const common::string &module, const log_level level)
{
    for (const auto sink : sinks_)
    {
        sink->log(message, module, level);
    }
}

} // namespace aeon::logger
