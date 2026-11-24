#include "riskforge/options/monte_carlo_greeks.hpp"
#include <gtest/gtest.h>
#include <cmath>
namespace{
    using riskforge::options::monte_carlo_call_delta;
    using riskforge::options::monte_carlo_call_gamma;
    using riskforge::options::monte_carlo_call_vega;
    using riskforge::simulation::GbmSimulationConfig;
    TEST(MonteCarloGreeksTest, CalculatesFiniteDelta){
        const GbmSimulationConfig config{100.0, 0.05, 0.20, 1.0, 50'000, 42u};
        const double delta=monte_carlo_call_delta(config, 100.0, 0.05, 8, 0.01);
        EXPECT_TRUE(std::isfinite(delta));
        EXPECT_GT(delta, 0.0);
        EXPECT_LT(delta, 1.0);
    }
    TEST(MonteCarloGreeksTest, CalculatesFiniteGamma){
        const GbmSimulationConfig config{100.0, 0.05, 0.20, 1.0, 50'000, 42u};
        const double gamma=monte_carlo_call_gamma(config, 100.0, 0.05, 8, 0.10);
        EXPECT_TRUE(std::isfinite(gamma));
        EXPECT_GT(gamma, 0.0);
    }
    TEST(MonteCarloGreeksTest, CalculatesFiniteVega){
        const GbmSimulationConfig config{100.0, 0.05, 0.20, 1.0, 50'000, 42u};
        const double vega=monte_carlo_call_vega(config, 100.0, 0.05, 8, 0.01);
        EXPECT_TRUE(std::isfinite(vega));
        EXPECT_GT(vega, 0.0);
    }
}