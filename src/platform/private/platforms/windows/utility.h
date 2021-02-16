#pragma once

#include "exception.h"

#include <string_view>

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

namespace aeon::platform::internal
{

[[nodiscard]] inline auto to_wstring(const std::u8string_view &src)
{
    const auto size = MultiByteToWideChar(CP_UTF8, 0, reinterpret_cast<LPCCH>(std::data(src)), -1, nullptr, 0);

    if (!size)
        throw windows_platform_exception{u8"Could not convert utf-8 to wstring."};

    std::wstring dst;
    dst.resize(size);

    if (!MultiByteToWideChar(CP_UTF8, 0, reinterpret_cast<LPCCH>(std::data(src)), -1,
                             static_cast<LPWSTR>(std::data(dst)), size))
        throw windows_platform_exception{u8"Could not convert utf-8 to wstring."};

    return dst;
}

[[nodiscard]] inline auto to_utf8string(const std::wstring &src)
{
    const auto size =
        WideCharToMultiByte(CP_UTF8, 0, reinterpret_cast<LPCWCH>(std::data(src)), -1, nullptr, 0, nullptr, nullptr);

    if (!size)
        throw windows_platform_exception{u8"Could not convert wstring to utf-8."};

    std::u8string dst;
    dst.resize(size);

    if (!WideCharToMultiByte(CP_UTF8, 0, static_cast<LPCWCH>(std::data(src)), -1,
                             reinterpret_cast<LPSTR>(std::data(dst)), size, nullptr, nullptr))
        throw windows_platform_exception{u8"Could not convert wstring to utf-8."};

    return dst;
}

[[noreturn]] inline void throw_last_error()
{
    std::wstring str;
    str.resize(4096);

    const auto error = GetLastError();
    FormatMessageW(FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS, nullptr, error,
                   MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), static_cast<LPWSTR>(std::data(str)),
                   static_cast<DWORD>(std::size(str)), nullptr);

    throw windows_platform_exception{error, to_utf8string(str)};
}

template <typename T>
inline void set_window_property(const HWND handle, const wchar_t *name, T *value)
{
    if (!SetPropW(handle, name, value))
        throw_last_error();
}

template <typename T>
[[nodiscard]] inline auto get_window_property(const HWND handle, const wchar_t *name)
{
    return static_cast<T *>(GetPropW(handle, name));
}

} // namespace aeon::platform::internal
