// Distributed under the BSD 2-Clause License - Copyright 2012-2022 Robin Degen

#pragma once

#include <aeon/imaging/image.h>
#include <aeon/imaging/exceptions.h>
#include <aeon/streams/idynamic_stream.h>
#include <filesystem>

namespace aeon::imaging::file::png
{

class load_exception : public imaging_exception
{
};

class save_exception : public imaging_exception
{
};

[[nodiscard]] auto load(const std::filesystem::path &path) -> image;
[[nodiscard]] auto load(streams::idynamic_stream &stream) -> image;

void save(const image_view &image, streams::idynamic_stream &stream);

void save(const image_view &image, const std::filesystem::path &path);

} // namespace aeon::imaging::file::png
