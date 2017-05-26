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

#include <gtest/gtest.h>
#include <aeon/mono/mono_jit.h>
#include <aeon/mono/mono_assembly.h>
#include <aeon/mono/mono_class.h>
#include <aeon/mono/mono_class_instance.h>
#include <aeon/mono/mono_method.h>
#include <aeon/mono/mono_exception.h>
#include <aeon/mono/mono_string.h>
#include "mono_jit_fixture.h"

TEST(test_mono, test_mono_jit_load_assembly_fail)
{
    aeon::mono::mono_jit &jit = mono_jit_fixture::get_singleton().get_jit();
    EXPECT_THROW(jit.load_assembly("some_assembly_that_doesnt_exist_12345.dll"), aeon::mono::mono_exception);
}

TEST(test_mono, test_mono_jit_load_assembly)
{
    aeon::mono::mono_jit &jit = mono_jit_fixture::get_singleton().get_jit();
    EXPECT_NO_THROW(jit.load_assembly("MonoTests.dll"));
}

TEST(test_mono, test_mono_jit_get_class_fail)
{
    aeon::mono::mono_jit &jit = mono_jit_fixture::get_singleton().get_jit();
    EXPECT_NO_THROW(aeon::mono::mono_assembly assembly = jit.load_assembly("MonoTests.dll");
                    EXPECT_THROW(aeon::mono::mono_class cls = assembly.get_class("SomeClassThatDoesntExist12345"),
                                 aeon::mono::mono_exception););
}

TEST(test_mono, test_mono_jit_get_class)
{
    aeon::mono::mono_jit &jit = mono_jit_fixture::get_singleton().get_jit();

    EXPECT_NO_THROW(aeon::mono::mono_assembly assembly = jit.load_assembly("MonoTests.dll");
                    aeon::mono::mono_class cls = assembly.get_class("ClassInstanceTest"););
}

TEST(test_mono, test_mono_jit_get_method)
{
    aeon::mono::mono_jit &jit = mono_jit_fixture::get_singleton().get_jit();

    EXPECT_NO_THROW(aeon::mono::mono_assembly assembly = jit.load_assembly("MonoTests.dll");

                    aeon::mono::mono_class cls = assembly.get_class("ClassInstanceTest");

                    aeon::mono::mono_class_instance obj = assembly.new_class_instance(cls);

                    aeon::mono::mono_method method_Method = obj.get_method("Method");
                    aeon::mono::mono_method method_MethodWithParameter = obj.get_method("MethodWithParameter", 1);
                    aeon::mono::mono_method method_MethodWithParameterAndReturnValue =
                        obj.get_method("MethodWithParameterAndReturnValue", 1););
}

static void MyObject_CreateInternal(MonoObject *this_ptr)
{
    std::cout << "MyObject created." << std::endl;
}

static void MyObject_DestroyInternal(MonoObject *this_ptr)
{
    std::cout << "MyObject deleted." << std::endl;
}

static void MyObject_DoStuff(MonoObject *this_ptr, MonoString *value)
{
    aeon::mono::mono_string str(value);
    std::string str_value = str.str();

    std::cout << "DoStuff was called with: " << str_value << std::endl;
}

TEST(test_mono, test_mono_call_native_methods)
{
    aeon::mono::mono_jit &jit = mono_jit_fixture::get_singleton().get_jit();
    aeon::mono::mono_jit::add_internal_call("Aeon.MyObject::CreateInternal", MyObject_CreateInternal);
    aeon::mono::mono_jit::add_internal_call("Aeon.MyObject::DestroyInternal", MyObject_DestroyInternal);
    aeon::mono::mono_jit::add_internal_call("Aeon.MyObject::DoStuff", MyObject_DoStuff);

    aeon::mono::mono_assembly assembly = jit.load_assembly("MonoTests.dll");
    aeon::mono::mono_class cls = assembly.get_class("ClassInstanceTest");
    aeon::mono::mono_class_instance obj = assembly.new_class_instance(cls);
}
