// Distributed under the BSD 2-Clause License - Copyright 2012-2019 Robin Degen

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
class mono_class_instance;
class mono_string;

class mono_assembly
{
public:
    mono_assembly() noexcept;
    explicit mono_assembly(MonoDomain *domain, MonoAssembly *assembly) noexcept;
    explicit mono_assembly(MonoDomain *domain, const std::string &path);
    ~mono_assembly();

    mono_assembly(const mono_assembly &) = delete;
    auto operator=(const mono_assembly &) -> mono_assembly & = delete;

    mono_assembly(mono_assembly &&o) noexcept;
    auto operator=(mono_assembly &&o) noexcept -> mono_assembly &;

    [[nodiscard]] auto get_mono_assembly_ptr() const noexcept -> MonoAssembly *;
    [[nodiscard]] auto get_mono_domain_ptr() const noexcept -> MonoDomain *;

    [[nodiscard]] auto get_class(const std::string &name) const -> mono_class;
    [[nodiscard]] auto get_class(const std::string &name_space, const std::string &name) const -> mono_class;

    [[nodiscard]] auto new_class_instance(const mono_class &cls) const noexcept -> mono_class_instance;
    [[nodiscard]] auto new_string(const std::string &str) const noexcept -> mono_string;

    [[nodiscard]] auto valid() const noexcept -> bool;

private:
    MonoDomain *domain_;
    MonoAssembly *assembly_;
    MonoImage *image_;
};

} // namespace aeon::mono
