#ifndef aeon_plugin_platform_h__
#define aeon_plugin_platform_h__

#if (AEON_PLATFORM_OS_WINDOWS)
#  define WIN32_LEAN_AND_MEAN
#  include <windows.h>
#  define AEON_LOAD_LIBRARY(path) (void *) LoadLibrary(path)
#  define AEON_GET_PROC_ADDRESS(handle, name) GetProcAddress((HMODULE) handle, name)
#  define AEON_CLOSE_LIBRARY(handle) FreeLibrary((HMODULE) handle)
#else
#  include <dlfcn.h>
#  define AEON_LOAD_LIBRARY(path) dlopen(path, RTLD_LAZY)
#  define AEON_GET_PROC_ADDRESS(handle, name) dlsym(handle, name)
#  define AEON_CLOSE_LIBRARY(handle) dlclose(handle)
#endif

#endif // aeon_plugin_platform_h__
