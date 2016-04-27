/*
 * ROBIN DEGEN; CONFIDENTIAL
 *
 * 2012 - 2016 Robin Degen
 * All Rights Reserved.
 *
 * NOTICE:  All information contained herein is, and remains the property of
 * Robin Degen and its suppliers, if any. The intellectual and technical
 * concepts contained herein are proprietary to Robin Degen and its suppliers
 * and may be covered by U.S. and Foreign Patents, patents in process, and are
 * protected by trade secret or copyright law. Dissemination of this
 * information or reproduction of this material is strictly forbidden unless
 * prior written permission is obtained from Robin Degen.
 */

#include <aeon/filesystem.h>
#include <aeon/platform.h>
#include <stdexcept>
#include <stdlib.h>
#include <stdio.h>

#if (defined(AEON_PLATFORM_OS_OSX) || defined(AEON_PLATFORM_OS_LINUX))
#include <unistd.h>
#elif(defined(AEON_PLATFORM_OS_WINDOWS))
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <io.h>
#endif

namespace aeon
{
namespace filesystem
{

bool exists(const std::string &path)
{
#if (defined(AEON_PLATFORM_OS_OSX) || defined(AEON_PLATFORM_OS_LINUX))
    return (access(path.c_str(), F_OK) != -1);
#elif(defined(AEON_PLATFORM_OS_WINDOWS))
    return ((_access(path.c_str(), 0)) != -1);
#else
    throw std::runtime_error("Filesystem is not yet implemented or untested for this platform.");
#endif
}

void delete_file(const std::string &path)
{
#if (defined(AEON_PLATFORM_OS_WINDOWS) || defined(AEON_PLATFORM_OS_OSX) || defined(AEON_PLATFORM_OS_LINUX))
    if (remove(path.c_str()) != 0)
        throw std::runtime_error("delete_file failed.");
#else
    throw std::runtime_error("Filesystem is not yet implemented or untested for this platform.");
#endif
}

void delete_directory(const std::string &path)
{
#if (defined(AEON_PLATFORM_OS_OSX) || defined(AEON_PLATFORM_OS_LINUX))
    if (rmdir(path.c_str()) != 0)
        throw std::runtime_error("delete_directory failed.");
#elif(defined(AEON_PLATFORM_OS_WINDOWS))
    if (RemoveDirectory(path.c_str()) != 0)
        throw std::runtime_error("delete_directory failed.");
#else
    throw std::runtime_error("Filesystem is not yet implemented or untested for this platform.");
#endif
}

std::string generate_temporary_file_path()
{
    char file_name_buff[512];
    char *file_path = tmpnam(file_name_buff);
    return file_path;
}

} // namespace filesystem
} // namespace aeon
