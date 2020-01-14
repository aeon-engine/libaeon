// Distributed under the BSD 2-Clause License - Copyright 2012-2020 Robin Degen

#pragma once

#include <aeon/fonts/glyph.h>
#include <aeon/streams/idynamic_stream.h>
#include <memory>
#include <vector>

// Forward declare for FreeType.
struct FT_LibraryRec_;

namespace aeon::fonts
{

class face_wrapper;

class face final
{
    friend class font_manager;

public:
    ~face();

    face(const face &) = delete;
    auto operator=(const face &) -> face & = delete;

    face(face &&) noexcept = default;
    auto operator=(face &&) noexcept -> face & = default;

    /*!
     * Load a glyph. Loading the next glyph will re-use the same buffer,
     * so be sure to copy the image somewhere first before loading the next glyph.
     */
    [[nodiscard]] auto load_glyph(const char32_t control_code) const -> glyph;

private:
    face(FT_LibraryRec_ *library, streams::idynamic_stream &stream, const float points, const int dpi);
    face(FT_LibraryRec_ *library, const std::vector<std::reference_wrapper<streams::idynamic_stream>> &streams,
         const float points, const int dpi);

    std::vector<std::unique_ptr<face_wrapper>> faces_;
};

} // namespace aeon::fonts
