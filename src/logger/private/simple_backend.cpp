// Distributed under the BSD 2-Clause License - Copyright 2012-2022 Robin Degen

#include <aeon/logger/simple_backend.h>
#include <iostream>

namespace aeon::logger
{

void simple_backend::log(const common::string &message, const common::string &module, const log_level level)
{
    std::cout << "[" << log_level_str[static_cast<int>(level)] << "] [" << module << "]: " << message << std::endl;
}

} // namespace aeon::logger
