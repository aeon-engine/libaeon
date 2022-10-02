// Distributed under the BSD 2-Clause License - Copyright 2012-2022 Robin Degen

#pragma once

#include <aeon/imaging/image.h>
#include <aeon/imaging/exceptions.h>
#include <filesystem>

namespace aeon::imaging::file
{

class unsupported_file_exception : public imaging_exception
{
};

[[nodiscard]] auto load(const std::filesystem::path &path) -> image;

} // namespace aeon::imaging::file
