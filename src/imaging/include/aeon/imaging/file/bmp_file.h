// Distributed under the BSD 2-Clause License - Copyright 2012-2020 Robin Degen

#pragma once

#include <aeon/imaging/dynamic_image.h>
#include <aeon/imaging/exceptions.h>
#include <aeon/streams/idynamic_stream.h>
#include <filesystem>

namespace aeon::imaging::file::bmp
{

class load_exception : public imaging_exception
{
};

[[nodiscard]] auto load(const std::filesystem::path &path) -> dynamic_image;
[[nodiscard]] auto load(streams::idynamic_stream &stream) -> dynamic_image;

} // namespace aeon::imaging::file::bmp
