// Distributed under the BSD 2-Clause License - Copyright 2012-2019 Robin Degen

#pragma once

#include <clang-c/Index.h>
#include <functional>

namespace aeon::clang
{

void clang_visit(const CXCursor cursor, std::function<void(const CXCursor, const CXCursor)> func);

} // namespace aeon::clang
