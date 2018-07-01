/*
 * Copyright (c) 2012-2018 Robin Degen
 *
 * Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this software and associated documentation
 * files (the "Software"), to deal in the Software without
 * restriction, including without limitation the rights to use,
 * copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following
 * conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
 * OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
 * HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 * WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 */

#pragma once

#include <aeon/logger/base_backend.h>
#include <aeon/logger/log_level.h>
#include <aeon/common/noncopyable.h>
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

class logger : public common::noncopyable
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

private:
    base_backend &backend_;
    std::string module_;
};

} // namespace aeon::logger
