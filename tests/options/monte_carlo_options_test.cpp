#include "riskforge/options/black_scholes.hpp"
#include "riskforge/options/monte_carlo_options.hpp"
#include "riskforge/options/black_scholes_put.hpp"
#include <gtest/gtest.h>
namespace{
    using riskforge::options::BlackScholesInput;
    using riskforge::options::black_scholes_call_price;
    using riskforge::options::black_scholes_put_price;
    using riskforge::options::monte_carlo_european_call_price;
    using riskforge::options::monte_carlo_european_put_price;
    using riskforge::simulation::GbmSimulationConfig;
    TEST(MonteCarloOptionsTest, CallPriceApproachesBlackScholesPrice){
        const GbmSimulationConfig config{
            100.0,
            0.05,
            0.20,
            1.0,
            100'000,
            42u
        };
        const BlackScholesInput analytical_input{
            100.0,
            100.0,
            0.05,
            0.20,
            1.0
        };
        const double analytical_price=black_scholes_call_price(analytical_input);
        const double monte_carlo_price=monte_carlo_european_call_price(config, 100.0, 0.05, 8);
        EXPECT_NEAR(monte_carlo_price, analytical_price, 0.15);
    }
    TEST(MonteCarloOptionsTest, PutPriceApproachesBlackScholesPrice){
        const GbmSimulationConfig config{
            100.0,
            0.05,
            0.20,
            1.0,
            100'000,
            42u
        };
        const BlackScholesInput analytical_input{
            100.0,
            100.0,
            0.05,
            0.20,
            1.0
        };
        const double analytical_price=black_scholes_put_price(analytical_input);
        const double monte_carlo_price=monte_carlo_european_put_price(config, 100.0, 0.05, 8);
        EXPECT_NEAR(monte_carlo_price, analytical_price, 0.15);
    }
}