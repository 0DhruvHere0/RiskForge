#include "riskforge/options/implied_volatility.hpp"
#include <gtest/gtest.h>
#include <stdexcept>
namespace{
    using riskforge::options::BlackScholesInput;
    using riskforge::options::black_scholes_implied_volatility;
    TEST(ImpliedVolatilityValidationTest, RejectsNegativeMarketPrice){
        const BlackScholesInput input{
            100.0,
            100.0,
            0.05,
            0.0,
            1.0
        };
        EXPECT_THROW(static_cast<void>(black_scholes_implied_volatility(input, -1.0)), std::invalid_argument);
    }
    TEST(ImpliedVolatilityValidationTest, RejectsPriceAboveSpot){
        const BlackScholesInput input{
            100.0,
            100.0,
            0.05,
            0.0,
            1.0
        };
        EXPECT_THROW(static_cast<void>(black_scholes_implied_volatility(input, 100.0)), std::invalid_argument);
    }
    TEST(ImpliedVolatilityValidationTest, RejectsZeroTime){
        const BlackScholesInput input{
            100.0,
            100.0,
            0.05,
            0.0,
            0.0
        };
        EXPECT_THROW(static_cast<void>(black_scholes_implied_volatility(input, 10.0)), std::domain_error);
    }
}