// Distributed under the BSD 2-Clause License - Copyright 2012-2020 Robin Degen

#pragma once

#include <aeon/logger/log_level.h>
#include <string>

namespace aeon::logger
{

class log_sink
{
public:
    log_sink() = default;
    virtual ~log_sink() = default;

    log_sink(const log_sink &) = delete;
    auto operator=(const log_sink &) noexcept -> log_sink & = delete;

    log_sink(log_sink &&) = delete;
    auto operator=(log_sink &&) noexcept -> log_sink & = delete;

    virtual void log(const std::string &message, const std::string &module, log_level level) = 0;
};

} // namespace aeon::logger
