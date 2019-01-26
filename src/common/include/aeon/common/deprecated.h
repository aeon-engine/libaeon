// Copyright (c) 2012-2019 Robin Degen

#pragma once

#if (defined(AEON_IGNORE_DEPRECATED))
#define AEON_DEPRECATED(message)
#else
#define AEON_DEPRECATED(message) [[deprecated(message)]]
#endif
