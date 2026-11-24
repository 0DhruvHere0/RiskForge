#include "riskforge/options/black_scholes.hpp"
#include "riskforge/options/volatility_surface.hpp"
#include <gtest/gtest.h>
namespace{
    using riskforge::options::BlackScholesInput;
    using riskforge::options::black_scholes_call_price;
    using riskforge::options::build_call_volatility_surface;
    TEST(VolatilitySurfaceTest, RecoversConstantVolatility){
        const BlackScholesInput base_input{
            100.0,
            100.0,
            0.05,
            0.20,
            1.0
        };
        const std::vector<double> strikes{
            90.0, 100.0, 110.0
        };
        std::vector<double> market_prices;
        for (const double strike : strikes){
            BlackScholesInput input=base_input;
            input.strike=strike;
            market_prices.push_back(black_scholes_call_price(input));
        }
        const auto volatilities=build_call_volatility_surface(base_input, strikes, market_prices);
        ASSERT_EQ(volatilities.size(), 3u);
        for (const double volatility : volatilities){
            EXPECT_NEAR(volatility, 0.20, 1e-8);
        }
    }
}