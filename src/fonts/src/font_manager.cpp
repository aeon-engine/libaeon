// Distributed under the BSD 2-Clause License - Copyright 2012-2019 Robin Degen

#include <aeon/fonts/font_manager.h>
#include <aeon/fonts/exceptions.h>

#include <ft2build.h>
#include <freetype/freetype.h>

namespace aeon::fonts
{

namespace internal
{

[[nodiscard]] auto create_freetype_library() -> FT_LibraryRec_ *
{
    FT_Library library = nullptr;

    if (FT_Init_FreeType(&library) != 0)
        throw font_exception{};

    return library;
}

void free_freetype_library(FT_LibraryRec_ *library)
{
    FT_Done_FreeType(library);
}

} // namespace internal

font_manager::font_manager()
    : freetype_{internal::create_freetype_library(), internal::free_freetype_library}
{
}

font_manager::~font_manager() = default;

[[nodiscard]] auto font_manager::load_face(streams::idynamic_stream &stream, const float points, const int dpi) const
    -> face
{
    return face{freetype_.get(), stream, points, dpi};
}

[[nodiscard]] auto
    font_manager::load_multi_face(const std::vector<std::reference_wrapper<streams::idynamic_stream>> &streams,
                                  const float points, const int dpi) const -> face
{
    return face{freetype_.get(), streams, points, dpi};
}

} // namespace aeon::fonts
