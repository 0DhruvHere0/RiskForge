#include "riskforge/simulation/monte_carlo.hpp"
#include "riskforge/simulation/parallel_monte_carlo.hpp"
#include <benchmark/benchmark.h>
#include <cstddef>
#include <utility>
namespace{
    void benchmark_serial_simulation(
        benchmark::State& state
    ){
        const riskforge::simulation::GbmSimulationConfig config{
            100.0,
            0.05,
            0.20,
            1.0,
            static_cast<std::size_t>(state.range(0)),
            42u
        };
        for (auto _ : state){
            auto prices=
                riskforge::simulation::
                simulate_gbm_terminal_prices(config);
            benchmark::DoNotOptimize(
                std::move(prices)
            );
            benchmark::ClobberMemory();
        }
    }
    void benchmark_parallel_simulation(
        benchmark::State& state
    ){
        const riskforge::simulation::GbmSimulationConfig config{
            100.0,
            0.05,
            0.20,
            1.0,
            static_cast<std::size_t>(state.range(0)),
            42u
        };
        for (auto _ : state){
            auto prices=
                riskforge::simulation::
                simulate_gbm_terminal_prices_parallel(
                    config,
                    4
                );
            benchmark::DoNotOptimize(
                std::move(prices)
            );
            benchmark::ClobberMemory();
        }
    }
}
BENCHMARK(benchmark_serial_simulation)
    ->Arg(10'000)
    ->Arg(100'000);
BENCHMARK(benchmark_parallel_simulation)
    ->Arg(10'000)
    ->Arg(100'000)
    ->UseRealTime();
BENCHMARK_MAIN();