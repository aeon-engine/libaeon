// Copyright (c) 2012-2019 Robin Degen

#pragma once

#include <aeon/imaging/dynamic_image.h>
#include <aeon/imaging/exceptions.h>
#include <aeon/streams/stream_fwd.h>
#include <aeon/common/stdfilesystem.h>

namespace aeon::imaging::file::bmp
{

class load_exception : public imaging_exception
{
};

auto load(const std::filesystem::path &path) -> dynamic_image;
auto load(streams::stream &stream) -> dynamic_image;

} // namespace aeon::imaging::file::bmp
