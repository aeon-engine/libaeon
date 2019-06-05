// Distributed under the BSD 2-Clause License - Copyright 2012-2019 Robin Degen

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
