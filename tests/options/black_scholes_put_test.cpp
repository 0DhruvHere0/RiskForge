#include "riskforge/options/black_scholes_put.hpp"
#include <gtest/gtest.h>
#include <cmath>
namespace{
    using riskforge::options::BlackScholesInput;
    using riskforge::options::black_scholes_put_delta;
    using riskforge::options::black_scholes_put_price;
    TEST(BlackScholesPutTest, CalculatesKnownPutPrice){
        const BlackScholesInput input{
            100.0,
            100.0,
            0.05,
            0.20,
            1.0
        };
        EXPECT_NEAR(black_scholes_put_price(input), 5.573526022256971, 1e-10);
    }
    TEST(BlackScholesPutTest, CalculatesKnownPutDelta){
        const BlackScholesInput input{
            100.0,
            100.0,
            0.05,
            0.20,
            1.0
        };
        EXPECT_NEAR(black_scholes_put_delta(input), -0.3631693488243809, 1e-10);
    }
    TEST(BlackScholesPutTest, SatisfiesPutCallParity){
        const BlackScholesInput input{
            100.0,
            100.0,
            0.05,
            0.20,
            1.0
        };
        const double call_price=black_scholes_call_price(input);
        const double put_price=black_scholes_put_price(input);
        const double discounted_strike=input.strike*std::exp(-input.risk_free_rate*input.time);
        EXPECT_NEAR(put_price, call_price-input.spot+discounted_strike, 1e-10);
    }
}