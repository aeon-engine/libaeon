// Distributed under the BSD 2-Clause License - Copyright 2012-2019 Robin Degen

#pragma once

#include <aeon/imaging/dynamic_image.h>
#include <aeon/imaging/exceptions.h>
#include <aeon/streams/idynamic_stream.h>
#include <filesystem>

namespace aeon::imaging::file::jpg
{

class load_exception : public imaging_exception
{
};

[[nodiscard]] auto load(const std::filesystem::path &path) -> dynamic_image;
[[nodiscard]] auto load(streams::idynamic_stream &stream) -> dynamic_image;

class save_exception : public imaging_exception
{
};

enum class subsample_mode
{
    subsample_444,
    subsample_440,
    subsample_422,
    subsample_420,
    subsample_411,
    subsample_grayscale
};

void save(const dynamic_image &image, const subsample_mode subsample, int quality, const std::filesystem::path &path);
void save(const dynamic_image &image, const subsample_mode subsample, int quality, streams::idynamic_stream &stream);

template <typename T>
void save(const image_view<T> &image, const subsample_mode subsample, int quality, const std::filesystem::path &path);

template <typename T>
void save(const image_view<T> &image, const subsample_mode subsample, int quality, streams::idynamic_stream &stream);

} // namespace aeon::imaging::file::jpg
