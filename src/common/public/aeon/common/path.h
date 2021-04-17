// Distributed under the BSD 2-Clause License - Copyright 2012-2021 Robin Degen

#pragma once

#include <aeon/common/platform.h>
#include <filesystem>

namespace aeon::common::path
{

/*!
 * Turn the given path into an absolute path as seen from the base path. If the given path is already an absolute path,
 * it is returned unaltered.
 *
 * Examples:
 * base_path = "C:\MyDir"
 * path = "Data\Test.txt"
 * returns: "C:\MyDir\Data\Test.txt"
 *
 * base_path = "C:\MyDir\Data"
 * path = "..\Test.txt"
 * returns: "C:\MyDir\Test.txt"
 *
 * base_path = "C:\MyDir"
 * path = "C:\Data\Test.txt"
 * returns: "C:\Data\Test.txt"
 */
[[nodiscard]] inline auto absolute_path(const std::filesystem::path &base_path, const std::filesystem::path &path)
{
    if (path.is_absolute())
        return path;

    return std::filesystem::weakly_canonical(base_path / path);
}

} // namespace aeon::common::path
