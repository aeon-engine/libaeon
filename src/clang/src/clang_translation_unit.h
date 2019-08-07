// Distributed under the BSD 2-Clause License - Copyright 2012-2019 Robin Degen

#pragma once

#include "clang_index.h"
#include <filesystem>
#include <array>
#include <vector>
#include <stdexcept>

namespace aeon::clang::internal
{

class clang_translation_unit final
{
public:
    explicit clang_translation_unit(const std::filesystem::path &path, const std::vector<const char *> &args)
        : index_{}
        , translation_unit_{nullptr}
    {
        const auto path_str = path.string();

        translation_unit_ =
            clang_parseTranslationUnit(index_.get(), path_str.c_str(), std::data(args),
                                       static_cast<int>(std::size(args)), nullptr, 0, CXTranslationUnit_KeepGoing);

        if (translation_unit_ == nullptr)
            throw std::runtime_error{{}};
    }

    ~clang_translation_unit()
    {
        clang_disposeTranslationUnit(translation_unit_);
    }

    clang_translation_unit(const clang_translation_unit &) = delete;
    auto operator=(const clang_translation_unit &) -> clang_translation_unit & = delete;

    clang_translation_unit(clang_translation_unit &&o) noexcept = delete;
    auto operator=(clang_translation_unit &&o) noexcept -> clang_translation_unit & = delete;

    auto get_cursor() const noexcept
    {
        return clang_getTranslationUnitCursor(translation_unit_);
    }

private:
    clang_index index_;
    CXTranslationUnit translation_unit_;
};

} // namespace aeon::clang::internal
