// Copyright (c) 2012-2019 Robin Degen

#include "mono_jit_fixture.h"
#include <aeon/mono/mono_string.h>

void MyObject_CreateInternal(MonoObject *this_ptr)
{
    std::cout << "MyObject created." << std::endl;
}

void MyObject_DestroyInternal(MonoObject *this_ptr)
{
    std::cout << "MyObject deleted." << std::endl;
}

void MyObject_DoStuff(MonoObject *this_ptr, std::string value)
{
    std::cout << "DoStuff was called with: " << value << std::endl;
}

std::string MyObject_ReturnAString(MonoObject *this_ptr, std::string value)
{
    std::cout << "ReturnAString was called with: " << value << std::endl;
    return "The value: " + value;
}

mono_jit_fixture *mono_jit_fixture::singleton_ = nullptr;

mono_jit_fixture::mono_jit_fixture()
    : jit_("Aeon Mono Test Jit")
{
    singleton_ = this;
}

void mono_jit_fixture::SetUp()
{
    aeon::mono::mono_jit::add_internal_call("Aeon.MyObject::CreateInternal",
                                            aeon_mono_auto_wrap(MyObject_CreateInternal));
    aeon::mono::mono_jit::add_internal_call("Aeon.MyObject::DestroyInternal",
                                            aeon_mono_auto_wrap(MyObject_DestroyInternal));
    aeon::mono::mono_jit::add_internal_call("Aeon.MyObject::DoStuff", aeon_mono_auto_wrap(MyObject_DoStuff));
    aeon::mono::mono_jit::add_internal_call("Aeon.MyObject::ReturnAString",
                                            aeon_mono_auto_wrap(MyObject_ReturnAString));
}

void mono_jit_fixture::TearDown()
{
}

aeon::mono::mono_jit &mono_jit_fixture::get_jit()
{
    assert(singleton_);
    return singleton_->jit_;
}
