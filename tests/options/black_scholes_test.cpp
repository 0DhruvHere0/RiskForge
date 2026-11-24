#include "riskforge/options/black_scholes.hpp"
#include <gtest/gtest.h>
namespace{
    using riskforge::options::BlackScholesInput;
    using riskforge::options::black_scholes_call_delta;
    using riskforge::options::black_scholes_call_price;
    TEST(BlackScholesTest, CalculatesKnownCallPrice){
        const BlackScholesInput input{
            100.0,
            100.0,
            0.05,
            0.20,
            1.0
        };
        EXPECT_NEAR(
            black_scholes_call_price(input),
            10.450583572185565,
            1e-10
        );
    }
    TEST(BlackScholesTest, CalculatesKnownCallDelta){
        const BlackScholesInput input{
            100.0,
            100.0,
            0.05,
            0.20,
            1.0
        };
        EXPECT_NEAR(
            black_scholes_call_delta(input),
            0.6368306511756191,
            1e-10
        );
    }
    TEST(BlackScholesTest, HandlesZeroTime){
        const BlackScholesInput input{
            110.0,
            100.0,
            0.05,
            0.20,
            0.0
        };
        EXPECT_DOUBLE_EQ(
            black_scholes_call_price(input),
            10.0
        );
        EXPECT_DOUBLE_EQ(
            black_scholes_call_delta(input),
            1.0
        );
    }
}