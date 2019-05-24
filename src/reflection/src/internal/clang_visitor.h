// Copyright (c) 2012-2019 Robin Degen

#pragma once

#include <clang-c/Index.h>
#include <functional>

namespace aeon::reflection::internal
{

inline void clang_visit(CXCursor cursor, std::function<void(CXCursor, CXCursor)> func)
{
    clang_visitChildren(
        cursor,
        [](CXCursor c, CXCursor parent, CXClientData client_data) {
            const auto func = static_cast<std::function<void(CXCursor, CXCursor)> *>(client_data);
            (*func)(c, parent);
            return CXChildVisit_Continue;
        },
        &func);
}

} // namespace aeon::reflection::internal
