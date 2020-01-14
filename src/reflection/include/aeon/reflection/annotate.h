// Distributed under the BSD 2-Clause License - Copyright 2012-2020 Robin Degen

#pragma once

#if (defined(__AEON_REFLECTION__))
#define __AEON_Q(x) #x
#define __AEON_QUOTE(x) __AEON_Q(x)
#define AEON_ANNOTATE(type) __attribute__((annotate(__AEON_QUOTE(type))))
#else
#define AEON_ANNOTATE(type)
#endif
