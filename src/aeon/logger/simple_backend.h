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

class simple_backend : public base_backend
{
public:
    void log(const std::string &message, const std::string &module, const log_level level) override
    {
        std::cout << "[" << log_level_str[static_cast<int>(level)] << "] [" << module << "]: " << message << std::endl;
    }
};

} // namespace logger
} // namespace aeon
