/*
 * Copyright (c) 2012-2017 Robin Degen
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

#include <aeon/mono/mono_exception.h>

namespace aeon
{
namespace mono
{

mono_exception::mono_exception()
    : std::runtime_error("Mono Exception.")
{
}

mono_exception::mono_exception(const std::string &what)
    : std::runtime_error(what.c_str())
{
}

mono_thunk_exception::mono_thunk_exception(MonoException *ex)
    : mono_thunk_exception(__get_exception_info(ex))
{
}

mono_thunk_exception::mono_thunk_exception(const exception_info &info)
    : mono_exception(info.exception_typename + "(" + info.message + ")")
    , exception_typename_(info.exception_typename)
    , message_(info.message)
    , stacktrace_(info.stacktrace)
{
}

auto mono_thunk_exception::__get_exception_info(MonoException *ex) -> exception_info
{
    auto exception_obj = reinterpret_cast<MonoObject *>(ex);
    auto exception_class = mono_object_get_class(exception_obj);
    auto exception_type = mono_class_get_type(exception_class);
    std::string exception_typename = mono_type_get_name(exception_type);
    std::string message = __get_string_property("Message", exception_class, exception_obj);
    std::string stacktrace = __get_string_property("StackTrace", exception_class, exception_obj);
    return {exception_typename, message, stacktrace};
}

auto mono_thunk_exception::__get_string_property(const char *property_name, MonoClass *cls, MonoObject *obj) -> char *
{
    auto property = mono_class_get_property_from_name(cls, property_name);
    auto getter = mono_property_get_get_method(property);
    auto value = reinterpret_cast<MonoString *>(mono_runtime_invoke(getter, obj, nullptr, nullptr));
    return mono_string_to_utf8(value);
}

} // namespace mono
} // namespace aeon
