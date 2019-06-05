// Distributed under the BSD 2-Clause License - Copyright 2012-2019 Robin Degen

#pragma once

#include <cstdio>

namespace aeon::common
{

void hexdump(FILE *dest, const void *src, size_t len) noexcept;

} // namespace aeon::common
