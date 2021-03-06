// Distributed under the BSD 2-Clause License - Copyright 2012-2021 Robin Degen

#pragma once

#include <aeon/common/flags.h>
#include <cstdint>

namespace aeon::ast
{

enum class access_specifier : std::uint32_t
{
    invalid_t = 0x01,
    public_t = 0x02,
    protected_t = 0x04,
    private_t = 0x08,
};

aeon_declare_flag_operators(access_specifier);

} // namespace aeon::ast
