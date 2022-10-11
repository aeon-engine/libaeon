// Distributed under the BSD 2-Clause License - Copyright 2012-2022 Robin Degen

#pragma once

#include <aeon/logger/log_level.h>
#include <aeon/common/string.h>

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

    virtual void log(const common::string &message, const common::string &module, const log_level level) = 0;
};

} // namespace aeon::logger
