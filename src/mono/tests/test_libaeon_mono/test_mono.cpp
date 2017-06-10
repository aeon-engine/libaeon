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
#include <aeon/mono/mono_thunk.h>
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

TEST(test_mono, test_mono_call_thunk)
{
    auto &jit = mono_jit_fixture::get_singleton().get_jit();
    auto assembly = jit.load_assembly("MonoTests.dll");
    auto cls = assembly.get_class("ClassInstanceTest");
    auto method_thunk = cls.get_static_function_thunk<int(int)>("FunctionWithIntParam");
    const auto number = 1000;
    auto result = method_thunk(number);
    ASSERT_EQ(number + 1337, result);
}

TEST(test_mono, test_mono_call_thunk2)
{
    auto &jit = mono_jit_fixture::get_singleton().get_jit();
    auto assembly = jit.load_assembly("MonoTests.dll");
    auto cls = assembly.get_class("ClassInstanceTest");
    auto method_thunk = cls.get_static_function_thunk<void(float, int, float)>("VoidFunction");
    method_thunk(13.37f, 42, 9000.0f);
}

TEST(test_mono, test_mono_call_thunk3)
{
    auto &jit = mono_jit_fixture::get_singleton().get_jit();
    auto assembly = jit.load_assembly("MonoTests.dll");
    auto cls = assembly.get_class("ClassInstanceTest");
    auto method_thunk = cls.get_static_function_thunk<void(std::string)>("FunctionWithStringParam");
    method_thunk("Hello!");
}

TEST(test_mono, test_mono_call_thunk4)
{
    auto &jit = mono_jit_fixture::get_singleton().get_jit();
    auto assembly = jit.load_assembly("MonoTests.dll");
    auto cls = assembly.get_class("ClassInstanceTest");
    auto method_thunk = cls.get_static_function_thunk<std::string(std::string)>("StringReturnFunction");
    auto expected_string = std::string("Hello!");
    auto result = method_thunk(expected_string);
    ASSERT_EQ(result, std::string("The string value was: " + expected_string));
}

TEST(test_mono, test_mono_call_thunk_with_exception)
{
    auto &jit = mono_jit_fixture::get_singleton().get_jit();
    auto assembly = jit.load_assembly("MonoTests.dll");
    auto cls = assembly.get_class("ClassInstanceTest");
    auto method_thunk = cls.get_static_function_thunk<void()>("ExceptionFunction");
    ASSERT_ANY_THROW(method_thunk());
}

TEST(test_mono, test_mono_call_method)
{
    auto &jit = mono_jit_fixture::get_singleton().get_jit();
    auto assembly = jit.load_assembly("MonoTests.dll");
    auto cls = assembly.get_class("ClassInstanceTest");
    auto cls_instance = assembly.new_class_instance(cls);
    auto method_thunk = cls_instance.get_method_thunk<void()>("Method");
    method_thunk();
}

TEST(test_mono, test_mono_call_method2)
{
    auto &jit = mono_jit_fixture::get_singleton().get_jit();
    auto assembly = jit.load_assembly("MonoTests.dll");
    auto cls = assembly.get_class("ClassInstanceTest");
    auto cls_instance = assembly.new_class_instance(cls);
    auto method_thunk = cls_instance.get_method_thunk<std::string(std::string)>("MethodWithParameterAndReturnValue");
    auto result = method_thunk("test");
    ASSERT_EQ("Return Value: test", result);
}
