// Distributed under the BSD 2-Clause License - Copyright 2012-2023 Robin Degen

#pragma once

#include <aeon/logger/log_level.h>
#include <aeon/common/string.h>

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

    [[nodiscard]] auto get_log_level() const -> log_level;

    virtual void log(const common::string &message, const common::string &module, const log_level level) = 0;

private:
    void handle_log(const common::string &message, const common::string &module, const log_level level);

    log_level level_;
};

} // namespace aeon::logger
