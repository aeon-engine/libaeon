/*
 * ROBIN DEGEN; CONFIDENTIAL
 *
 * 2012 - 2016 Robin Degen
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

class base_backend : public utility::noncopyable
{
    friend class logger_stream;

public:
    base_backend()
        : level_(log_level::message)
    {
    }

    base_backend(const log_level level)
        : level_(level)
    {
    }

    virtual ~base_backend() = default;

    void set_log_level(const log_level level)
    {
        level_ = level;
    }

    auto get_log_level() const -> log_level
    {
        return level_;
    }

    virtual void log(const std::string &message, const std::string &module, const log_level level) = 0;

private:
    void __handle_log(const std::string &message, const std::string &module, const log_level level)
    {
        if (level >= level_)
            log(message, module, level);
    }

    log_level level_;
};

} // namespace logger
} // namespace aeon
