// Distributed under the BSD 2-Clause License - Copyright 2012-2020 Robin Degen

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
    const auto &jit = mono_jit_fixture::get_jit();
    EXPECT_THROW(const auto assembly = jit.load_assembly("some_assembly_that_doesnt_exist_12345.dll"); (void)assembly;
                 , aeon::mono::mono_exception);
}

TEST(test_mono, test_mono_jit_load_assembly)
{
    const auto &jit = mono_jit_fixture::get_jit();
    EXPECT_NO_THROW(const auto assembly = jit.load_assembly("MonoTests.dll"); (void)assembly;);
}

TEST(test_mono, test_mono_jit_get_class_fail)
{
    const auto &jit = mono_jit_fixture::get_jit();
    EXPECT_NO_THROW(const auto assembly = jit.load_assembly("MonoTests.dll");
                    EXPECT_THROW(const auto cls = assembly.get_class("SomeClassThatDoesntExist12345"),
                                 aeon::mono::mono_exception););
}

TEST(test_mono, test_mono_jit_get_class)
{
    const auto &jit = mono_jit_fixture::get_jit();

    EXPECT_NO_THROW(const auto assembly = jit.load_assembly("MonoTests.dll");
                    const auto cls = assembly.get_class("ClassInstanceTest"););
}

TEST(test_mono, test_mono_jit_get_method)
{
    const auto &jit = mono_jit_fixture::get_jit();

    EXPECT_NO_THROW(const auto assembly = jit.load_assembly("MonoTests.dll");

                    const auto cls = assembly.get_class("ClassInstanceTest");

                    const auto obj = assembly.new_class_instance(cls);

                    const auto method_Method = obj.get_method("Method");
                    const auto method_MethodWithParameter = obj.get_method("MethodWithParameter", 1);
                    const auto method_MethodWithParameterAndReturnValue =
                        obj.get_method("MethodWithParameterAndReturnValue", 1););
}

TEST(test_mono, test_mono_call_thunk)
{
    const auto &jit = mono_jit_fixture::get_jit();
    const auto assembly = jit.load_assembly("MonoTests.dll");
    const auto cls = assembly.get_class("ClassInstanceTest");
    const auto method_thunk = cls.get_static_function_thunk<int(int)>("FunctionWithIntParam");
    const auto number = 1000;
    auto result = method_thunk(number);
    ASSERT_EQ(number + 1337, result);
}

TEST(test_mono, test_mono_call_thunk2)
{
    const auto &jit = mono_jit_fixture::get_jit();
    const auto assembly = jit.load_assembly("MonoTests.dll");
    const auto cls = assembly.get_class("ClassInstanceTest");
    const auto method_thunk = cls.get_static_function_thunk<void(float, int, float)>("VoidFunction");
    method_thunk(13.37f, 42, 9000.0f);
}

TEST(test_mono, test_mono_call_thunk3)
{
    const auto &jit = mono_jit_fixture::get_jit();
    const auto assembly = jit.load_assembly("MonoTests.dll");
    const auto cls = assembly.get_class("ClassInstanceTest");
    const auto method_thunk = cls.get_static_function_thunk<void(std::string)>("FunctionWithStringParam");
    method_thunk("Hello!");
}

TEST(test_mono, test_mono_call_thunk4)
{
    const auto &jit = mono_jit_fixture::get_jit();
    const auto assembly = jit.load_assembly("MonoTests.dll");
    const auto cls = assembly.get_class("ClassInstanceTest");
    const auto method_thunk = cls.get_static_function_thunk<std::string(std::string)>("StringReturnFunction");
    const auto expected_string = std::string("Hello!");
    const auto result = method_thunk(expected_string);
    ASSERT_EQ(result, std::string("The string value was: " + expected_string));
}

TEST(test_mono, test_mono_call_thunk_with_exception)
{
    const auto &jit = mono_jit_fixture::get_jit();
    const auto assembly = jit.load_assembly("MonoTests.dll");
    const auto cls = assembly.get_class("ClassInstanceTest");
    const auto method_thunk = cls.get_static_function_thunk<void()>("ExceptionFunction");
    ASSERT_ANY_THROW(method_thunk());
}

TEST(test_mono, test_mono_call_method)
{
    const auto &jit = mono_jit_fixture::get_jit();
    const auto assembly = jit.load_assembly("MonoTests.dll");
    const auto cls = assembly.get_class("ClassInstanceTest");
    const auto cls_instance = assembly.new_class_instance(cls);
    const auto method_thunk = cls_instance.get_method_thunk<void()>("Method");
    method_thunk();
}

TEST(test_mono, test_mono_call_method2)
{
    const auto &jit = mono_jit_fixture::get_jit();
    const auto assembly = jit.load_assembly("MonoTests.dll");
    const auto cls = assembly.get_class("ClassInstanceTest");
    const auto cls_instance = assembly.new_class_instance(cls);
    const auto method_thunk =
        cls_instance.get_method_thunk<std::string(std::string)>("MethodWithParameterAndReturnValue");
    const auto result = method_thunk("test");
    ASSERT_EQ("Return Value: test", result);
}
