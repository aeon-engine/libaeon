/*
 * ROBIN DEGEN; CONFIDENTIAL
 *
 * 2012 - 2017 Robin Degen
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

#define AEON_LOG(log, level) log(level)
#define AEON_LOG_FATAL(log) AEON_LOG(log, aeon::logger::log_level::fatal)
#define AEON_LOG_ERROR(log) AEON_LOG(log, aeon::logger::log_level::error)
#define AEON_LOG_WARNING(log) AEON_LOG(log, aeon::logger::log_level::warning)
#define AEON_LOG_MESSAGE(log) AEON_LOG(log, aeon::logger::log_level::message)
#define AEON_LOG_DEBUG(log) AEON_LOG(log, aeon::logger::log_level::debug)
#define AEON_LOG_TRACE(log) AEON_LOG(log, aeon::logger::log_level::trace)

namespace aeon
{
namespace logger
{

class logger_stream
{
public:
    logger_stream(base_backend &backend, const std::string &module, const log_level level)
        : backend_(backend)
        , module_(module)
        , level_(level)
    {
    }

    void operator<<(std::ostream &(std::ostream &)) const
    {
        auto message = stream_.str();
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

class logger : public utility::noncopyable
{
public:
    logger(base_backend &backend, const std::string &module)
        : backend_(backend)
        , module_(module)
    {
    }

    auto operator()(const log_level level) const -> logger_stream
    {
        return logger_stream(backend_, module_, level);
    }

private:
    base_backend &backend_;
    std::string module_;
};

} // namespace logger
} // namespace aeon
