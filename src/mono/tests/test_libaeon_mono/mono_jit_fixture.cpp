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

#include "mono_jit_fixture.h"
#include <aeon/mono/mono_string.h>

aeon_utility_initialize_singleton(mono_jit_fixture);

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

mono_jit_fixture::mono_jit_fixture()
    : jit_("Aeon Mono Test Jit")
{
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
    return jit_;
}
