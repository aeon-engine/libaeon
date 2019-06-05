// Distributed under the BSD 2-Clause License - Copyright 2012-2019 Robin Degen

#pragma once

#include <aeon/logger/log_level.h>
#include <string>

namespace aeon::logger
{

class base_backend
{
    friend class logger_stream;

public:
    base_backend();

    explicit base_backend(const log_level level);

    virtual ~base_backend() = default;

    base_backend(const base_backend &) = delete;
    auto operator=(const base_backend &) noexcept -> base_backend & = delete;

    base_backend(base_backend &&) = delete;
    auto operator=(base_backend &&) noexcept -> base_backend & = delete;

    void set_log_level(const log_level level);

    auto get_log_level() const -> log_level;

    virtual void log(const std::string &message, const std::string &module, const log_level level) = 0;

private:
    void __handle_log(const std::string &message, const std::string &module, const log_level level);

    log_level level_;
};

} // namespace aeon::logger
