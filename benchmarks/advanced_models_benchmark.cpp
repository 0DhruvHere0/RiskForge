#include "riskforge/simulation/jump_diffusion.hpp"
#include "riskforge/simulation/stochastic_volatility.hpp"
#include "riskforge/simulation/student_t_gbm.hpp"
#include <benchmark/benchmark.h>
#include <utility>
namespace{
    void benchmark_student_t_gbm(benchmark::State& state){
        for (auto _ :state){
            double price= riskforge::simulation::student_t_gbm_terminal_price(100.0, 0.05, 0.20, 1.0, 8.0, 42u, static_cast<std::uint64_t>(state.iterations()));
            benchmark::DoNotOptimize(std::move(price));
            benchmark::ClobberMemory();
        }
    }
    void benchmark_stochastic_volatility(benchmark::State& state){
        for (auto _ :state){
            double price= riskforge::simulation::stochastic_volatility_terminal_price(100.0, 0.05, 0.04, 0.04, 2.0, 0.10, 1.0, 100, 42u, static_cast<std::uint64_t>(state.iterations()));
            benchmark::DoNotOptimize(std::move(price));
            benchmark::ClobberMemory();
        }
    }
    void benchmark_jump_diffusion(benchmark::State& state){
        for (auto _ :state){
            double price= riskforge::simulation::jump_diffusion_terminal_price(100.0, 0.05, 0.20, 0.4, -0.10, 0.20, 1.0, 42u, static_cast<std::uint64_t>(state.iterations()));
            benchmark::DoNotOptimize(std::move(price));
            benchmark::ClobberMemory();
        }
    }
}
BENCHMARK(benchmark_student_t_gbm);
BENCHMARK(benchmark_stochastic_volatility);
BENCHMARK(benchmark_jump_diffusion);
BENCHMARK_MAIN();