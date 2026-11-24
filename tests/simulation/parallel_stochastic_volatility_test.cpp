#include "riskforge/simulation/parallel_stochastic_volatility.hpp"
#include "riskforge/simulation/stochastic_volatility.hpp"
#include <gtest/gtest.h>
namespace{
    using riskforge::simulation::parallel_stochastic_volatility_terminal_prices;
    using riskforge::simulation::stochastic_volatility_terminal_price;
    TEST(ParallelStochasticVolatilityTest, MatchesSerialSimulation){
        const auto parallel=parallel_stochastic_volatility_terminal_prices(100.0, 0.05, 0.04, 0.04, 2.0, 0.10, 1.0, 100, 128, 4, 42u);
        for (std::size_t path=0; path<parallel.size(); ++path){
            EXPECT_DOUBLE_EQ(parallel[path], stochastic_volatility_terminal_price(100.0, 0.05, 0.04, 0.04, 2.0, 0.10, 1.0, 100, 42u, static_cast<std::uint64_t>(path)));
        }
    }
    TEST(ParallelStochasticVolatilityTest, HandlesMoreWorkersThanPaths){
        const auto prices=parallel_stochastic_volatility_terminal_prices(100.0, 0.05, 0.04, 0.04, 2.0, 0.10, 1.0, 100, 8, 32, 42u);
        EXPECT_EQ(prices.size(), 8u);
    }
}