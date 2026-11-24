#include "riskforge/options/black_scholes.hpp"
#include "riskforge/options/implied_volatility.hpp"
#include <gtest/gtest.h>
namespace{
    using riskforge::options::BlackScholesInput;
    using riskforge::options::black_scholes_call_price;
    using riskforge::options::black_scholes_implied_volatility;
    TEST(ImpliedVolatilityTest, RecoversKnownVolatility){
        const BlackScholesInput input{
            100.0,
            100.0,
            0.05,
            0.20,
            1.0
        };
        const double market_price=black_scholes_call_price(input);
        BlackScholesInput solver_input=input;
        solver_input.volatility=0.0;
        EXPECT_NEAR(black_scholes_implied_volatility(solver_input, market_price), 0.20, 1e-8);
    }
    TEST(ImpliedVolatilityTest, RecoversHigherVolatility){
        const BlackScholesInput input{
            100.0,
            110.0,
            0.03,
            0.35,
            2.0
        };
        const double market_price=black_scholes_call_price(input);
        BlackScholesInput solver_input=input;
        solver_input.volatility=0.0;
        EXPECT_NEAR(black_scholes_implied_volatility(solver_input, market_price), 0.35, 1e-8);
    }
}