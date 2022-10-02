// Distributed under the BSD 2-Clause License - Copyright 2012-2022 Robin Degen

#pragma once

#include <cstdio>

namespace aeon::common::hexdump
{

void pretty_print(FILE *dest, const void *src, const std::size_t len) noexcept;
void cpp_array(FILE *dest, const char *const array_name, const void *src, const std::size_t len) noexcept;

} // namespace aeon::common::hexdump
