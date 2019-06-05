// Distributed under the BSD 2-Clause License - Copyright 2012-2019 Robin Degen

#pragma once

#include "gtest/gtest.h"
#include <aeon/mono/mono_jit.h>

// The Mono Jit can only be instanced once during runtime, so it needs to be done in a global fixture.
class mono_jit_fixture : public ::testing::Environment
{
public:
    mono_jit_fixture();

    void SetUp() override;
    void TearDown() override;

    static aeon::mono::mono_jit &get_jit();

private:
    static mono_jit_fixture *singleton_;
    aeon::mono::mono_jit jit_;
};
