# Distributed under the BSD 2-Clause License - Copyright 2012-2020 Robin Degen

include(Benchmark)

add_benchmark_suite(
    NO_BENCHMARK_MAIN
    TARGET benchmark_libaeon_math
    SOURCES
        main.cpp
        benchmark_mat3.cpp
        benchmark_mat3_sse.cpp
        benchmark_mat4.cpp
        benchmark_mat4_sse.cpp
    INCLUDES
        ${CMAKE_CURRENT_BINARY_DIR}
    LIBRARIES aeon_math
    FOLDER dep/libaeon/benchmarks
)
