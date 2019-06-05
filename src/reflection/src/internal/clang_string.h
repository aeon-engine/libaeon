// Distributed under the BSD 2-Clause License - Copyright 2012-2019 Robin Degen

#pragma once

#include <clang-c/Index.h>
#include <clang-c/CXString.h>
#include <string>

namespace aeon::reflection::internal
{

inline auto to_string(const CXString str)
{
    std::string stdstr = clang_getCString(str);
    clang_disposeString(str);
    return stdstr;
}

} // namespace aeon::reflection::internal
