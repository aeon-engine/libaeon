// Distributed under the BSD 2-Clause License - Copyright 2012-2020 Robin Degen

#include <aeon/common/dll_loader.h>
#include <aeon/common/platform.h>

#include <cassert>

#if (defined(AEON_PLATFORM_OS_WINDOWS))
#if (defined(UNICODE))
#include <aeon/common/utf8_convert.h>
#endif
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
static const std::string dll_extension = ".dll";
#elif (defined(AEON_PLATFORM_OS_LINUX))
#include <dlfcn.h>
static const std::string dll_extension = ".so";
#elif (defined(AEON_PLATFORM_OS_MACOS))
#include <dlfcn.h>
static const std::string dll_extension = ".dylib";
#endif

namespace aeon::common::dll_loader
{

#if (defined(AEON_PLATFORM_OS_WINDOWS))
dll_handle get_dll_handle(const std::string &filename)
{
    const auto real_filename = filename + dll_extension;

#if (defined(UNICODE))
    const auto wstr_filename = utf8::to_wstring(real_filename);
    return LoadLibrary(wstr_filename.c_str());
#else
    return LoadLibrary(real_filename.c_str());
#endif
}

void free_dll_handle(const dll_handle handle)
{
    if (handle)
        FreeLibrary(static_cast<HMODULE>(handle));
}

void *get_dll_proc_address(const dll_handle handle, const char *proc)
{
    return reinterpret_cast<void *>(GetProcAddress(static_cast<HMODULE>(handle), proc));
}

#elif (defined(AEON_PLATFORM_OS_LINUX) || defined(AEON_PLATFORM_OS_MACOS))
dll_handle get_dll_handle(const std::string &filename)
{
#if (defined(AEON_PLATFORM_OS_LINUX))
    // On linux, the given path must be prepended by "./", otherwise
    // the .so file will not get loaded as expected.
    //
    // From the documentation (https://linux.die.net/man/3/dlopen):
    // "If filename contains a slash ("/"), then it is interpreted as a
    // (relative or absolute) pathname. Otherwise, the dynamic linker searches
    // for the library (...)"
    const auto real_filename = "./" + filename + dll_extension;
#else
    const auto real_filename = filename + dll_extension;
#endif
    return dlopen(real_filename.c_str(), RTLD_LAZY);
}

void free_dll_handle(const dll_handle handle)
{
    if (handle)
        dlclose(handle);
}

void *get_dll_proc_address(const dll_handle handle, const char *proc)
{
    return dlsym(handle, proc);
}
#endif

} // namespace aeon::common::dll_loader
