// Distributed under the BSD 2-Clause License - Copyright 2012-2022 Robin Degen

#pragma once

using CXIndex = void *;

namespace aeon::clang
{

class clang_index final
{
public:
    clang_index();
    ~clang_index();

    clang_index(const clang_index &) = delete;
    auto operator=(const clang_index &) -> clang_index & = delete;

    clang_index(clang_index &&) noexcept = delete;
    auto operator=(clang_index &&) noexcept -> clang_index & = delete;

    [[nodiscard]] auto get() const noexcept -> CXIndex;

private:
    CXIndex index_;
};

} // namespace aeon::clang
