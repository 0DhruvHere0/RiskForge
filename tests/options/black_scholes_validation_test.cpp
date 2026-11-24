#include "riskforge/options/black_scholes.hpp"
#include <gtest/gtest.h>
#include <stdexcept>
namespace{
    using riskforge::options::BlackScholesInput;
    using riskforge::options::black_scholes_call_delta;
    using riskforge::options::black_scholes_call_price;
    TEST(BlackScholesValidationTest, RejectsNonPositiveSpot){
        const BlackScholesInput input{
            0.0,
            100.0,
            0.05,
            0.20,
            1.0
        };
        EXPECT_THROW(
            static_cast<void>(black_scholes_call_price(input)),
            std::invalid_argument
        );
    }
    TEST(BlackScholesValidationTest, RejectsNonPositiveStrike){
        const BlackScholesInput input{
            100.0,
            0.0,
            0.05,
            0.20,
            1.0
        };
        EXPECT_THROW(
            static_cast<void>(black_scholes_call_delta(input)),
            std::invalid_argument
        );
    }
    TEST(BlackScholesValidationTest, RejectsNegativeVolatility){
        const BlackScholesInput input{
            100.0,
            100.0,
            0.05,
            -0.20,
            1.0
        };
        EXPECT_THROW(
            static_cast<void>(black_scholes_call_price(input)),
            std::invalid_argument
        );
    }
    TEST(BlackScholesValidationTest, RejectsNegativeTime){
        const BlackScholesInput input{
            100.0,
            100.0,
            0.05,
            0.20,
            -1.0
        };
        EXPECT_THROW(
            static_cast<void>(black_scholes_call_delta(input)),
            std::invalid_argument
        );
    }
}