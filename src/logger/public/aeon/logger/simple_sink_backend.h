// Distributed under the BSD 2-Clause License - Copyright 2012-2022 Robin Degen

#pragma once

#include <aeon/logger/log_sink.h>
#include <aeon/logger/base_backend.h>
#include <aeon/logger/log_level.h>
#include <set>

namespace aeon::logger
{

class simple_sink_backend : public base_backend
{
public:
    simple_sink_backend();

    explicit simple_sink_backend(const log_level level);

    void add_sink(log_sink *sink);

    void remove_all_sinks();

private:
    void log(const std::string &message, const std::string &module, const log_level level) override;

    std::set<log_sink *> sinks_;
};

} // namespace aeon::logger
