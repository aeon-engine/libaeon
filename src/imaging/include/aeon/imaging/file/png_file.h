// Copyright (c) 2012-2019 Robin Degen

#pragma once

#include <aeon/imaging/image.h>
#include <aeon/imaging/dynamic_image.h>
#include <aeon/imaging/exceptions.h>
#include <aeon/streams/stream_fwd.h>
#include <aeon/common/stdfilesystem.h>

namespace aeon::imaging::file::png
{

class load_exception : public imaging_exception
{
};

class save_exception : public imaging_exception
{
};

auto load(const std::filesystem::path &path) -> dynamic_image;
auto load(streams::stream &stream) -> dynamic_image;

void save(const dynamic_image &image, const std::filesystem::path &path);
void save(const dynamic_image &image, streams::stream &stream);

template <typename T>
void save(const image_view<T> &image, const std::filesystem::path &path);

template <typename T>
void save(const image_view<T> &image, streams::stream &stream);

} // namespace aeon::imaging::file::png
