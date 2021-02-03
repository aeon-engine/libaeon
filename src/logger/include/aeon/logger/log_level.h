// Distributed under the BSD 2-Clause License - Copyright 2012-2021 Robin Degen

#pragma once

namespace aeon::logger
{

enum class log_level : int
{
    trace = 0,
    debug = 1,
    message = 2,
    warning = 3,
    error = 4,
    fatal = 5
};

static const char *log_level_str[] = {"Trace", "Debug", "Message", "Warning", "Error", "Fatal"};

} // namespace aeon::logger
