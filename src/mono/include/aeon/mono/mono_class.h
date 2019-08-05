// Distributed under the BSD 2-Clause License - Copyright 2012-2019 Robin Degen

#pragma once

#if (AEON_PLATFORM_OS_WINDOWS)
#ifndef MONO_DLL_IMPORT
#define MONO_DLL_IMPORT
#endif
#endif

#include <aeon/mono/mono_static_function.h>
#include <aeon/common/type_traits.h>
#include <aeon/common/compilers.h>

AEON_IGNORE_VS_WARNING_PUSH(4201)
#include <mono/jit/jit.h>
AEON_IGNORE_VS_WARNING_POP()

#include <string>

namespace aeon::mono
{

class mono_assembly;
class mono_class_field;

class mono_class
{
public:
    mono_class() noexcept;
    explicit mono_class(const mono_assembly *assembly, MonoClass *cls) noexcept;
    explicit mono_class(const mono_assembly *assembly, MonoImage *image, const std::string &name);
    explicit mono_class(const mono_assembly *assembly, MonoImage *image, const std::string &name_space,
                        const std::string &name);
    virtual ~mono_class();

    mono_class(const mono_class &) = delete;
    [[nodiscard]] auto operator=(const mono_class &) -> mono_class & = delete;

    mono_class(mono_class &&o) noexcept;
    [[nodiscard]] auto operator=(mono_class &&o) noexcept -> mono_class &;

    [[nodiscard]] auto get_static_function(const std::string &name, int argc = 0) const -> mono_static_function;

    template <typename function_signature_t>
    [[nodiscard]] auto get_static_function_thunk(const std::string &name) const;

    [[nodiscard]] auto get_mono_class_ptr() const noexcept -> MonoClass *;

    [[nodiscard]] auto get_field(const std::string &name) const -> mono_class_field;

private:
    MonoClass *class_;
    const mono_assembly *assembly_;
};

template <typename function_signature_t>
[[nodiscard]] auto mono_class::get_static_function_thunk(const std::string &name) const
{
    constexpr auto arg_count = common::type_traits::function_signature_argument_count<function_signature_t>::value;
    auto func = get_static_function(name, arg_count);
    return func.template get_thunk<function_signature_t>();
}

} // namespace aeon::mono
