// Distributed under the BSD 2-Clause License - Copyright 2012-2019 Robin Degen

#pragma once

#include <clang-c/Index.h>
#include <functional>

namespace aeon::clang::internal
{

inline void clang_visit(CXCursor cursor, std::function<void(CXCursor, CXCursor)> func)
{
    clang_visitChildren(
        cursor,
        [](const CXCursor c, const CXCursor parent, const CXClientData client_data) {
            const auto func = static_cast<std::function<void(const CXCursor, const CXCursor)> *>(client_data);
            (*func)(c, parent);
            return CXChildVisit_Continue;
        },
        &func);
}

} // namespace aeon::clang::internal
