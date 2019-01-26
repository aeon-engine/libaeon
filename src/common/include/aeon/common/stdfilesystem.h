// Copyright (c) 2012-2019 Robin Degen

#pragma once

#include <aeon/common/platform.h>

#if (defined(AEON_PLATFORM_OS_WINDOWS))
#include <filesystem>
#elif (defined(AEON_PLATFORM_OS_LINUX))
#if __GNUC__ >= 8
#include <filesystem>
#else
#include <experimental/filesystem>
namespace std
{
namespace filesystem = ::std::experimental::filesystem;
}
#endif
#elif (defined(AEON_PLATFORM_OS_OSX))
#include <experimental/filesystem>
namespace std
{
namespace filesystem = ::std::experimental::filesystem;
}
#endif
