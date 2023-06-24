// Distributed under the BSD 2-Clause License - Copyright 2012-2023 Robin Degen

#include <aeon/fonts/face.h>
#include <aeon/fonts/face_wrapper.h>
#include <aeon/streams/stream.h>

namespace aeon::fonts
{

face::face(FT_LibraryRec_ *library, streams::idynamic_stream &stream, const float points, const int dpi)
{
    faces_.emplace_back(std::make_unique<face_wrapper>(library, stream, points, dpi));
}

face::face(FT_LibraryRec_ *library, const std::vector<std::reference_wrapper<streams::idynamic_stream>> &streams,
           const float points, const int dpi)
{
    for (const auto &stream : streams)
    {
        faces_.emplace_back(std::make_unique<face_wrapper>(library, stream, points, dpi));
    }
}

face::~face() = default;

auto face::load_first_glyph() const -> std::tuple<char32_t, glyph>
{
    for (const auto &face : faces_)
    {
        const auto [control_code, char_index] = face->load_first_index();

        if (char_index == 0)
            continue;

        return {control_code, face->load_glyph(char_index)};
    }

    return {0, faces_.at(0)->load_glyph(0)};
}

auto face::load_next_glyph(const char32_t control_code) const -> std::tuple<char32_t, glyph>
{
    for (const auto &face : faces_)
    {
        const auto [next_control_code, char_index] = face->load_next_index(control_code);

        if (char_index == 0)
            continue;

        return {next_control_code, face->load_glyph(char_index)};
    }

    return {0, faces_.at(0)->load_glyph(0)};
}

[[nodiscard]] auto face::load_glyph(const char32_t control_code) const -> glyph
{
    for (const auto &face : faces_)
    {
        const auto char_index = face->get_char_index(control_code);

        if (char_index == 0)
            continue;

        return face->load_glyph(char_index);
    }

    // If none of the fonts have the glyph, grab the special glyph from the first face.
    return faces_.at(0)->load_glyph(0);
}

auto face::line_height() const -> float
{
    auto line_height = 0.0f;

    for (const auto &face : faces_)
    {
        if (face->line_height() > line_height)
            line_height = face->line_height();
    }

    return line_height;
}

} // namespace aeon::fonts
