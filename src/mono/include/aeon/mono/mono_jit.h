/*
 * Copyright (c) 2012-2018 Robin Degen
 *
 * Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this software and associated documentation
 * files (the "Software"), to deal in the Software without
 * restriction, including without limitation the rights to use,
 * copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following
 * conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
 * OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
 * HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 * WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 */

#pragma once

#if (AEON_PLATFORM_OS_WINDOWS)
#ifndef MONO_DLL_IMPORT
#define MONO_DLL_IMPORT
#endif
#endif

#include <aeon/mono/mono_type_conversion.h>
#include <mono/jit/jit.h>
#include <string>
#include <cassert>

namespace aeon::mono
{

class mono_assembly;

/*!
 * Class to initialize the Mono JIT. This class must be instanced
 * only once. When this class is deleted, the JIT is cleaned up.
 *
 * Due to the way Mono works, a cleaned up JIT can not be reinitialized
 * at runtime after it was cleaned up. You must keep this class instanced
 * during the full runtime of the application.
 */
class mono_jit
{
public:
    mono_jit();
    explicit mono_jit(const std::string &domain);
    ~mono_jit();

    mono_jit(const mono_jit &) = delete;
    auto operator=(const mono_jit &) -> mono_jit & = delete;

    mono_jit(mono_jit &&o) = delete;
    auto operator=(mono_jit &&o) -> mono_jit & = delete;

    auto load_assembly(const std::string &path) const -> mono_assembly;

    template <typename T>
    static void add_internal_call(const std::string &name, T func);

    static void set_auto_wrap_assembly(const mono_assembly &assembly);

    static auto get_auto_wrap_assembly() -> mono_assembly &;

private:
    static void __add_internal_call(const std::string &name, const void *func);
    MonoDomain *domain_;
    static mono_assembly internal_call_assembly_;
};

template <typename T>
inline void mono_jit::add_internal_call(const std::string &name, T func)
{
    __add_internal_call(name, reinterpret_cast<const void *>(func));
}

template <typename signature_t, signature_t &signature, class enable = void>
struct mono_jit_internal_call_wrapper;

template <typename... args_t, void (&func)(args_t...)>
struct mono_jit_internal_call_wrapper<void(args_t...), func>
{
    static void wrapper(typename convert_mono_type<args_t>::mono_type_name... args)
    {
        func(convert_mono_type<args_t>::from_mono(std::move(args))...);
    }
};

template <typename return_t, typename... args_t, return_t (&func)(args_t...)>
struct mono_jit_internal_call_wrapper<return_t(args_t...), func,
                                      typename std::enable_if<!std::is_void_v<return_t>>::type>
{
    static typename convert_mono_type<return_t>::mono_type_name
        wrapper(typename convert_mono_type<args_t>::mono_type_name... args)
    {
        auto &internal_call_assembly = mono_jit::get_auto_wrap_assembly();
        assert(internal_call_assembly.valid() &&
               "Internal call assembly not set. Call mono_jit::set_auto_wrap_assembly before execution.");
        return convert_mono_type<return_t>::to_mono(internal_call_assembly,
                                                    func(convert_mono_type<args_t>::from_mono(std::move(args))...));
    }
};

/*!
 * Wrap a non-static function for mono_jit::add_internal_call, where automatic type
 * converstion is done through convert_mono_type. Add your own specialisation implementation
 * of this class to support more types.
 */
#define aeon_mono_auto_wrap(func) &aeon::mono::mono_jit_internal_call_wrapper<decltype(func), func>::wrapper

} // namespace aeon::mono
