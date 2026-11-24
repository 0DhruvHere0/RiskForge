#include "riskforge/options/black_scholes_put.hpp"
#include <gtest/gtest.h>
#include <stdexcept>
namespace{
    using riskforge::options::BlackScholesInput;
    using riskforge::options::black_scholes_put_delta;
    using riskforge::options::black_scholes_put_price;
    TEST(BlackScholesPutValidationTest, RejectsInvalidSpot){
        const BlackScholesInput input{
            0.0,
            100.0,
            0.05,
            0.20,
            1.0
        };
        EXPECT_THROW(static_cast<void>(black_scholes_put_price(input)), std::invalid_argument);
    }
    TEST(BlackScholesPutValidationTest, RejectsInvalidStrike){
        const BlackScholesInput input{
            100.0,
            0.0,
            0.05,
            0.20,
            1.0
        };
        EXPECT_THROW(static_cast<void>(black_scholes_put_delta(input)), std::invalid_argument);
    }
    TEST(BlackScholesPutValidationTest, RejectsNegativeVolatility){
        const BlackScholesInput input{
            100.0,
            100.0,
            0.05,
            -0.20,
            1.0
        };
        EXPECT_THROW(static_cast<void>(black_scholes_put_price(input)), std::invalid_argument);
    }
}