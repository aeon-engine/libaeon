// Distributed under the BSD 2-Clause License - Copyright 2012-2021 Robin Degen

#include <aeon/logger/simple_backend.h>
#include <iostream>

namespace aeon::logger
{

void simple_backend::log(const std::string &message, const std::string &module, const log_level level)
{
    std::cout << "[" << log_level_str[static_cast<int>(level)] << "] [" << module << "]: " << message << std::endl;
}

} // namespace aeon::logger
