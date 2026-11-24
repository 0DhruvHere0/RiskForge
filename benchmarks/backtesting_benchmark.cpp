#include "riskforge/backtesting/historical_risk.hpp"
#include "riskforge/backtesting/rolling_historical_risk.hpp"
#include <benchmark/benchmark.h>
#include <utility>
#include <vector>
#include <cmath>
namespace{
    std::vector<double> create_returns(std::size_t count){
        std::vector<double> returns;
        returns.reserve(count);
        for (std::size_t index=0; index<count; ++index){
            returns.push_back(
                0.001*std::sin(static_cast<double>(index))
            );
        }
        return returns;
    }
    static void benchmark_historical_risk(benchmark::State& state){
        const auto returns=create_returns(
            static_cast<std::size_t>(state.range(0))
        );
        for (auto _: state){
            auto result=riskforge::backtesting::estimate_historical_risk(
                returns,
                0.95
            );
            benchmark::DoNotOptimize(std::move(result));
            benchmark::ClobberMemory();
        }
    }
    static void benchmark_rolling_historical_risk(benchmark::State& state){
        const auto returns=create_returns(
            static_cast<std::size_t>(state.range(0))
        );
        for (auto _: state){
            auto results=
                riskforge::backtesting::rolling_historical_risk(
                    returns,
                    250u,
                    0.95
                );
            benchmark::DoNotOptimize(std::move(results));
            benchmark::ClobberMemory();
        }
    }

}
BENCHMARK(benchmark_historical_risk)
    ->Arg(1000)
    ->Arg(10000)
    ->UseRealTime();
BENCHMARK(benchmark_rolling_historical_risk)
    ->Arg(1000)
    ->Arg(10000)
    ->UseRealTime();
BENCHMARK_MAIN();