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

#pragma once

#include <immintrin.h>

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
