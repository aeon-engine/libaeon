// Copyright (c) 2012-2019 Robin Degen

#pragma once

#include <cstdio>

namespace aeon::utility
{

void hexdump(FILE *dest, const void *src, size_t len) noexcept;

} // namespace aeon::utility
