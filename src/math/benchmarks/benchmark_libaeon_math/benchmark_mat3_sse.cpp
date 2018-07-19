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

#include <benchmark/benchmark.h>

#include <aeon/math/mat4.h>

using namespace aeon;

#if (!defined(AEON_DISABLE_SSE))

static void benchmark_mat3_sse_multiply_identity(benchmark::State &state)
{
    const auto mat1 = math::mat3::indentity();
    const auto mat2 = math::mat3::indentity();

    benchmark::DoNotOptimize(mat1);
    benchmark::DoNotOptimize(mat2);

    for (auto _ : state)
        benchmark::DoNotOptimize(mat1 * mat2);
}

BENCHMARK(benchmark_mat3_sse_multiply_identity);

static void benchmark_mat3_sse_multiply_rotation_with_identity(benchmark::State &state)
{
    const auto mat1 = math::mat3::indentity();
    const auto mat2 = math::mat3::rotate(10.0f);

    benchmark::DoNotOptimize(mat1);
    benchmark::DoNotOptimize(mat2);

    for (auto _ : state)
        benchmark::DoNotOptimize(mat1 * mat2);
}

BENCHMARK(benchmark_mat3_sse_multiply_rotation_with_identity);

#endif
