// Distributed under the BSD 2-Clause License - Copyright 2012-2021 Robin Degen

#include <aeon/imaging/file/file.h>
#include <aeon/imaging/file/bmp_file.h>
#include <aeon/imaging/file/jpg_file.h>
#include <aeon/imaging/file/png_file.h>
#include <aeon/common/string.h>

namespace aeon::imaging::file
{

[[nodiscard]] auto load(const std::filesystem::path &path) -> image
{
    if (!path.has_extension())
        throw unsupported_file_exception{};

    const auto extension = path.extension().string();

    // The checks here are sorted by expected usage frequency
    if (common::string::iequals<char>(extension, ".png"))
    {
        return png::load(path);
    }
    else if (common::string::iequals<char>(extension, ".jpg") || common::string::iequals<char>(extension, ".jpeg"))
    {
        return jpg::load(path);
    }
    else if (common::string::iequals<char>(extension, ".bmp"))
    {
        return bmp::load(path);
    }

    throw unsupported_file_exception{};
}

} // namespace aeon::imaging::file
