// Copyright (c) 2012-2019 Robin Degen

#pragma once

#include <aeon/fonts/face.h>
#include <aeon/fonts/config.h>
#include <aeon/streams/idynamic_stream.h>
#include <memory>
#include <vector>
#include <functional>

// Forward declare for FreeType.
struct FT_LibraryRec_;

namespace aeon::fonts
{

namespace internal
{

[[nodiscard]] auto create_freetype_library() -> FT_LibraryRec_ *;
void free_freetype_library(FT_LibraryRec_ *library);

} // namespace internal

class font_manager
{
public:
    font_manager();
    ~font_manager();

    font_manager(const font_manager &) = delete;
    auto operator=(const font_manager &) -> font_manager & = delete;

    font_manager(font_manager &&) noexcept = delete;
    auto operator=(font_manager &&) noexcept -> font_manager & = delete;

    [[nodiscard]] auto load_face(streams::idynamic_stream &stream, const float points = AEON_FONT_DEFAULT_POINTS,
                                 const int dpi = AEON_FONT_DEFAULT_DPI) const -> face;

    [[nodiscard]] auto load_multi_face(const std::vector<std::reference_wrapper<streams::idynamic_stream>> &streams,
                                       const float points = AEON_FONT_DEFAULT_POINTS,
                                       const int dpi = AEON_FONT_DEFAULT_DPI) const -> face;

private:
    std::unique_ptr<FT_LibraryRec_, decltype(&internal::free_freetype_library)> freetype_;
};

} // namespace aeon::fonts
