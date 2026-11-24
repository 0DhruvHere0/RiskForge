#include "riskforge/options/put_greeks.hpp"
#include <gtest/gtest.h>
#include <stdexcept>
namespace{
    using riskforge::options::BlackScholesInput;
    using riskforge::options::black_scholes_put_gamma;
    using riskforge::options::black_scholes_put_theta;
    TEST(PutGreeksValidationTest, RejectsZeroVolatility){
        const BlackScholesInput input{
            100.0,
            100.0,
            0.05,
            0.0,
            1.0
        };
        EXPECT_THROW(static_cast<void>(black_scholes_put_gamma(input)), std::domain_error);
    }
    TEST(PutGreeksValidationTest, RejectsZeroTime){
        const BlackScholesInput input{
            100.0,
            100.0,
            0.05,
            0.20,
            0.0
        };
        EXPECT_THROW(static_cast<void>(black_scholes_put_theta(input)), std::domain_error);
    }
}