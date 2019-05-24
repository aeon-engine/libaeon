// Copyright (c) 2012-2019 Robin Degen

#pragma once

#include <clang-c/Index.h>

namespace aeon::reflection::internal
{

class clang_index final
{
public:
    clang_index()
        : index_{clang_createIndex(0, 0)}
    {
    }

    ~clang_index()
    {
        clang_disposeIndex(index_);
    }

    clang_index(const clang_index &) = delete;
    auto operator=(const clang_index &) -> clang_index & = delete;

    clang_index(clang_index &&o) noexcept = delete;
    auto operator=(clang_index &&o) noexcept -> clang_index & = delete;

    auto get() const noexcept
    {
        return index_;
    }

private:
    CXIndex index_;
};

} // namespace aeon::reflection::internal
