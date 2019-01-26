// Copyright (c) 2012-2019 Robin Degen

#pragma once

#if (AEON_PLATFORM_OS_WINDOWS)
#ifndef MONO_DLL_IMPORT
#define MONO_DLL_IMPORT
#endif
#endif

#include <aeon/mono/mono_object.h>
#include <mono/jit/jit.h>
#include <string>

namespace aeon::mono
{

class mono_string : public mono_object
{
public:
    explicit mono_string(MonoString *mono_string) noexcept;
    explicit mono_string(MonoDomain *domain, const std::string &str) noexcept;
    virtual ~mono_string();

    mono_string(const mono_string &) = delete;
    auto operator=(const mono_string &) -> mono_string & = delete;

    mono_string(mono_string &&o) noexcept;
    auto operator=(mono_string &&o) noexcept -> mono_string &;

    auto operator=(const std::string &str) noexcept -> mono_string &;

    auto str() const -> std::string;

    auto get_mono_string() const -> MonoString *;

private:
    MonoDomain *domain_;
};

} // namespace aeon::mono
