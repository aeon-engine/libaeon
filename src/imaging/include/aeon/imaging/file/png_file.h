// Distributed under the BSD 2-Clause License - Copyright 2012-2021 Robin Degen

#pragma once

#include <aeon/imaging/image.h>
#include <aeon/imaging/dynamic_image.h>
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

[[nodiscard]] auto load(const std::filesystem::path &path) -> dynamic_image;
[[nodiscard]] auto load(streams::idynamic_stream &stream) -> dynamic_image;

void save(const dynamic_image &image, const std::filesystem::path &path);
void save(const dynamic_image &image, streams::idynamic_stream &stream);

template <typename T>
void save(const image_view<T> &image, const std::filesystem::path &path);

template <typename T>
void save(const image_view<T> &image, streams::idynamic_stream &stream);

} // namespace aeon::imaging::file::png
