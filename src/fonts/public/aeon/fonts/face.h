// Distributed under the BSD 2-Clause License - Copyright 2012-2021 Robin Degen

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
     * Get the first valid control code and its glyph index
     * \return Tuple of the control code and the glyph index
     */
    [[nodiscard]] auto load_first_glyph() const -> std::tuple<char32_t, glyph>;

    /*!
     * Get the next valid control code and its glyph index from the given control code
     * \return Tuple of the control code and the glyph index
     */
    [[nodiscard]] auto load_next_glyph(const char32_t control_code) const -> std::tuple<char32_t, glyph>;

    /*!
     * Load a glyph. Loading the next glyph will re-use the same buffer,
     * so be sure to copy the image somewhere first before loading the next glyph.
     */
    [[nodiscard]] auto load_glyph(const char32_t control_code) const -> glyph;

    /*!
     * Get the default line height in pixels
     */
    [[nodiscard]] auto line_height() const -> int;

private:
    face(FT_LibraryRec_ *library, streams::idynamic_stream &stream, const float points, const int dpi);
    face(FT_LibraryRec_ *library, const std::vector<std::reference_wrapper<streams::idynamic_stream>> &streams,
         const float points, const int dpi);

    std::vector<std::unique_ptr<face_wrapper>> faces_;
};

} // namespace aeon::fonts
