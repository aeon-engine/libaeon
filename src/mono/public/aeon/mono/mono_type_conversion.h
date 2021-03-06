// Distributed under the BSD 2-Clause License - Copyright 2012-2021 Robin Degen

#pragma once

#if (AEON_PLATFORM_OS_WINDOWS)
#ifndef MONO_DLL_IMPORT
#define MONO_DLL_IMPORT
#endif
#endif

#include <aeon/mono/mono_assembly.h>
#include <aeon/mono/mono_string.h>
#include <string>

namespace aeon::mono
{

template <typename T>
struct convert_mono_type
{
    using mono_type_name = T;

    [[nodiscard]] static auto to_mono(const mono_assembly &, T &&t) noexcept -> T
    {
        return std::forward<T>(t);
    }

    [[nodiscard]] static auto from_mono(T &&t) noexcept -> T
    {
        return std::forward<T>(t);
    }
};

template <>
struct convert_mono_type<std::string>
{
    using mono_type_name = MonoString *;

    [[nodiscard]] static auto to_mono(const mono_assembly &assembly, const std::string &str) -> MonoString *
    {
        return assembly.new_string(str).get_mono_string();
    }

    [[nodiscard]] static auto from_mono(MonoString *mono_str) -> std::string
    {
        return mono_string(mono_str).str();
    }
};

} // namespace aeon::mono
