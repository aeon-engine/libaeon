// Copyright (c) 2012-2019 Robin Degen

#pragma once

#include <immintrin.h>

#ifndef _mm_loadu_si16
#define _mm_loadu_si16(p) _mm_cvtsi32_si128(*(unsigned short const *)(p))
#endif

#ifndef _mm_loadu_si32
#define _mm_loadu_si32(p) _mm_cvtsi32_si128(*(unsigned int const *)(p))
#endif

#ifndef _mm_loadu_si64
#define _mm_loadu_si64(p) _mm_loadl_epi64((__m128i const *)(p))
#endif

#ifndef _mm_storeu_si16
#define _mm_storeu_si16(p, a) (void)(*(short *)(p) = (short)_mm_cvtsi128_si32((a)))
#endif

#ifndef _mm_storeu_si32
#define _mm_storeu_si32(p, a) (void)(*(int *)(p) = _mm_cvtsi128_si32((a)))
#endif

#ifndef _mm_storeu_si64
#define _mm_storeu_si64(p, a) (_mm_storel_epi64((__m128i *)(p), (a)))
#endif

/*!
 * Load 3 consecutive unaligned floats into an __m128.
 */
#define aeon_mm_load_ps96(p) _mm_castsi128_ps(_mm_unpacklo_epi64(_mm_loadu_si64(p), _mm_loadu_si32(&p[2])))

/*!
 * Store the lower 3 floats from an __m128 into memory (unaligned).
 */
#define aeon_mm_store_ps96(p, a)                                                                                       \
    _mm_storeu_si64(p, _mm_castps_si128(a));                                                                           \
    _mm_storeu_si32(&p[2], _mm_bsrli_si128(_mm_castps_si128(a), 8))
