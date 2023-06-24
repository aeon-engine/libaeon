// Distributed under the BSD 2-Clause License - Copyright 2012-2023 Robin Degen

#include <aeon/common/dynamic_library.h>
#include <aeon/common/platform.h>

#if (defined(AEON_PLATFORM_OS_WINDOWS))
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#else
#include <dlfcn.h>
#endif

namespace aeon::common
{

namespace internal
{

[[nodiscard]] static auto load_library(const std::filesystem::path &path) noexcept -> void *
{
#if (defined(AEON_PLATFORM_OS_WINDOWS))
    auto result = LoadLibraryW(path.wstring().c_str());
#else
    auto result = dlopen(reinterpret_cast<const char *>(path.u8string().c_str()), RTLD_LAZY | RTLD_LOCAL);
#endif

    return result;
}

[[nodiscard]] static auto get_proc_address(void *handle, const string_view &name) noexcept -> void *
{
#if (defined(AEON_PLATFORM_OS_WINDOWS))
    return reinterpret_cast<void *>(GetProcAddress(static_cast<const HMODULE>(handle), std::data(name)));
#else
    return dlsym(handle, std::data(name));
#endif
}

void free_library(void *handle) noexcept
{
#if (defined(AEON_PLATFORM_OS_WINDOWS))
    FreeLibrary(static_cast<HMODULE>(handle));
#else
    dlclose(handle);
#endif
}

} // namespace internal

dynamic_library::dynamic_library() noexcept
    : handle_{nullptr}
{
}

dynamic_library::dynamic_library(void *handle) noexcept
    : handle_{handle}
{
}

dynamic_library::dynamic_library(const std::filesystem::path &path) noexcept
    : handle_{internal::load_library(path)}
{
}

dynamic_library::~dynamic_library()
{
    destroy();
}

dynamic_library::dynamic_library(dynamic_library &&other) noexcept
    : handle_{other.handle_}
{
    other.handle_ = nullptr;
}

auto dynamic_library::operator=(dynamic_library &&other) noexcept -> dynamic_library &
{
    if (this != &other) [[likely]]
    {
        destroy();
        handle_ = other.handle_;
        other.handle_ = nullptr;
    }

    return *this;
}

auto dynamic_library::is_valid() const noexcept -> bool
{
    return handle_ != nullptr;
}

auto dynamic_library::handle() const noexcept -> void *
{
    return handle_;
}

auto dynamic_library::get_proc_address(const string_view &name) const noexcept -> void *
{
    return internal::get_proc_address(handle_, name);
}

auto dynamic_library::release() noexcept -> void *
{
    const auto handle = handle_;
    handle_ = nullptr;
    return handle;
}

void dynamic_library::destroy()
{
    if (handle_)
        internal::free_library(handle_);

    handle_ = nullptr;
}

} // namespace aeon::common
