// Distributed under the BSD 2-Clause License - Copyright 2012-2020 Robin Degen

#pragma once

#if (AEON_PLATFORM_OS_WINDOWS)
#ifndef MONO_DLL_IMPORT
#define MONO_DLL_IMPORT
#endif
#endif

#include <aeon/common/compilers.h>

AEON_IGNORE_VS_WARNING_PUSH(4201)
#include <mono/jit/jit.h>
AEON_IGNORE_VS_WARNING_POP()

namespace aeon::mono
{

class mono_object
{
public:
    mono_object() noexcept;
    explicit mono_object(MonoObject *object) noexcept;
    virtual ~mono_object();

    [[nodiscard]] auto get_mono_object() const noexcept -> MonoObject *;

    mono_object(const mono_object &) = default;
    auto operator=(const mono_object &) -> mono_object & = default;

    mono_object(mono_object &&) noexcept = default;
    auto operator=(mono_object &&) noexcept -> mono_object & = default;

protected:
    MonoObject *object_;
};

} // namespace aeon::mono
