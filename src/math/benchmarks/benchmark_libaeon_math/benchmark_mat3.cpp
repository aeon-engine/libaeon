// Distributed under the BSD 2-Clause License - Copyright 2012-2020 Robin Degen

#include <benchmark/benchmark.h>

#define AEON_DISABLE_SSE
#include <aeon/math/mat3.h>

using namespace aeon;

static void benchmark_mat3_multiply_identity(benchmark::State &state)
{
    const auto mat1 = math::mat3::indentity();
    const auto mat2 = math::mat3::indentity();

    benchmark::DoNotOptimize(mat1);
    benchmark::DoNotOptimize(mat2);

    for ([[maybe_unused]] auto _ : state)
        benchmark::DoNotOptimize(mat1 * mat2);
}

BENCHMARK(benchmark_mat3_multiply_identity);

static void benchmark_mat3_multiply_rotation_with_identity(benchmark::State &state)
{
    const auto mat1 = math::mat3::indentity();
    const auto mat2 = math::mat3::rotate(10.0f);

    benchmark::DoNotOptimize(mat1);
    benchmark::DoNotOptimize(mat2);

    for ([[maybe_unused]] auto _ : state)
        benchmark::DoNotOptimize(mat1 * mat2);
}

BENCHMARK(benchmark_mat3_multiply_rotation_with_identity);
