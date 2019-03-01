// Copyright (c) 2012-2019 Robin Degen

#pragma once

#include <aeon/logger/base_backend.h>
#include <aeon/logger/log_level.h>
#include <string>
#include <sstream>

#define AEON_LOG(log, level) log(level)
#define AEON_LOG_FATAL(log) AEON_LOG(log, aeon::logger::log_level::fatal)
#define AEON_LOG_ERROR(log) AEON_LOG(log, aeon::logger::log_level::error)
#define AEON_LOG_WARNING(log) AEON_LOG(log, aeon::logger::log_level::warning)
#define AEON_LOG_MESSAGE(log) AEON_LOG(log, aeon::logger::log_level::message)
#define AEON_LOG_DEBUG(log) AEON_LOG(log, aeon::logger::log_level::debug)
#define AEON_LOG_TRACE(log) AEON_LOG(log, aeon::logger::log_level::trace)

namespace aeon::logger
{

class logger_stream
{
public:
    logger_stream(base_backend &backend, std::string module, const log_level level)
        : backend_{backend}
        , module_{std::move(module)}
        , level_{level}
    {
    }

    ~logger_stream() = default;

    logger_stream(const logger_stream &) noexcept = delete;
    auto operator=(const logger_stream &) noexcept -> logger_stream & = delete;

    logger_stream(logger_stream &&) noexcept = delete;
    auto operator=(logger_stream &&) noexcept -> logger_stream & = delete;

    void operator<<(std::ostream &(std::ostream &)) const
    {
        const auto message = stream_.str();
        backend_.__handle_log(message, module_, level_);
    }

    template <typename T>
    auto &operator<<(const T &data)
    {
        stream_ << data;
        return *this;
    }

private:
    base_backend &backend_;
    std::string module_;
    log_level level_;
    std::stringstream stream_;
};

class logger
{
public:
    logger(base_backend &backend, std::string module)
        : backend_{backend}
        , module_{std::move(module)}
    {
    }

    auto operator()(const log_level level) const -> logger_stream
    {
        return logger_stream(backend_, module_, level);
    }

    logger(const logger &) noexcept = delete;
    auto operator=(const logger &) noexcept -> logger & = delete;

    logger(logger &&) noexcept = delete;
    auto operator=(logger &&) noexcept -> logger & = delete;

private:
    base_backend &backend_;
    std::string module_;
};

} // namespace aeon::logger
