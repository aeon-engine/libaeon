// Distributed under the BSD 2-Clause License - Copyright 2012-2020 Robin Degen

#pragma once

#include <aeon/clang/index.h>
#include <clang-c/Index.h>
#include <filesystem>
#include <vector>

namespace aeon::clang
{

class translation_unit final
{
public:
    explicit translation_unit(const std::filesystem::path &path, const std::vector<const char *> &args);

    ~translation_unit();

    translation_unit(const translation_unit &) = delete;
    auto operator=(const translation_unit &) -> translation_unit & = delete;

    translation_unit(translation_unit &&o) noexcept = delete;
    auto operator=(translation_unit &&o) noexcept -> translation_unit & = delete;

    [[nodiscard]] auto get_clang_translation_unit() const noexcept -> CXTranslationUnit;

    [[nodiscard]] auto get_cursor() const noexcept -> CXCursor;

private:
    clang_index index_;
    CXTranslationUnit translation_unit_;
};

} // namespace aeon::clang
