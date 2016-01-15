/*
 * ROBIN DEGEN; CONFIDENTIAL
 *
 * 2012 - 2015 Robin Degen
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

#if (defined(AEON_PLATFORM_OS_OSX))
#include <unistd.h>
#elif (defined(AEON_PLATFORM_OS_WINDOWS))
#include <io.h>
#endif

namespace aeon
{
namespace filesystem
{

bool exists(const std::string &path)
{
#if (defined(AEON_PLATFORM_OS_OSX))
    return (access(path.c_str(), F_OK) != -1);
#elif (defined(AEON_PLATFORM_OS_WINDOWS))
    return ((_access(path.c_str(), 0)) != -1);
#else
    throw std::runtime_error("Filesystem is not yet implemented or untested for this platform.");
#endif
}

} // namespace filesystem
} // namespace aeon
