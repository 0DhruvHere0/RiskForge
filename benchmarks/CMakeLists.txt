include(FetchContent)
FetchContent_Declare(
    benchmark
    URL https://github.com/google/benchmark/archive/refs/tags/v1.8.3.tar.gz
)
set(BENCHMARK_ENABLE_TESTING OFF CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(benchmark)
add_executable(
    riskforge_benchmark
    monte_carlo_benchmark.cpp
)
target_compile_features(
    riskforge_benchmark
    PRIVATE
        cxx_std_20
)
target_link_libraries(
    riskforge_benchmark
    PRIVATE
        riskforge
        benchmark::benchmark
)