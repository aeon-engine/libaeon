// Distributed under the BSD 2-Clause License - Copyright 2012-2022 Robin Degen

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

#include <string>

namespace aeon::mono
{

class mono_class;

class mono_class_field
{
public:
    mono_class_field() noexcept;
    explicit mono_class_field(mono_class &monoclass, const std::string &name) noexcept;
    explicit mono_class_field(MonoClass *monoclass, const std::string &name) noexcept;
    ~mono_class_field();

    mono_class_field(const mono_class_field &) = delete;
    auto operator=(const mono_class_field &) -> mono_class_field & = delete;

    mono_class_field(mono_class_field &&) noexcept;
    auto operator=(mono_class_field &&) noexcept -> mono_class_field &;

    [[nodiscard]] auto get_mono_class_field_ptr() const noexcept -> MonoClassField *;

private:
    MonoClassField *field_;
};

} // namespace aeon::mono
