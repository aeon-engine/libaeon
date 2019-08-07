// Distributed under the BSD 2-Clause License - Copyright 2012-2019 Robin Degen

#pragma once

/*!
 * I'll remember the good things how can you forget all the years that we shared in our way
 * Things were changing my life, taking your place in my life and our time drifting away.
 *
 * - On Reflection, Gentle Giant (1975)
 */

#if (defined(__AEON_REFLECTION__))
#define __AEON_Q(x) #x
#define __AEON_QUOTE(x) __AEON_Q(x)
#define AEON_ANNOTATE(type) __attribute__((annotate(__AEON_QUOTE(type))))
#else
#define AEON_ANNOTATE(type)
#endif
