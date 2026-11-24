#include "riskforge/options/greeks.hpp"
#include <gtest/gtest.h>
#include <stdexcept>
namespace{
    using riskforge::options::BlackScholesInput;
    using riskforge::options::black_scholes_call_gamma;
    using riskforge::options::black_scholes_call_rho;
    using riskforge::options::black_scholes_call_theta;
    using riskforge::options::black_scholes_call_vega;
    TEST(GreeksValidationTest, RejectsZeroVolatility){
        const BlackScholesInput input{
            100.0,
            100.0,
            0.05,
            0.0,
            1.0
        };
        EXPECT_THROW(static_cast<void>(black_scholes_call_gamma(input)), std::domain_error);
        EXPECT_THROW(static_cast<void>(black_scholes_call_vega(input)), std::domain_error);
    }
    TEST(GreeksValidationTest, RejectsZeroTime){
        const BlackScholesInput input{
            100.0,
            100.0,
            0.05,
            0.20,
            0.0
        };
        EXPECT_THROW(static_cast<void>(black_scholes_call_theta(input)), std::domain_error);
        EXPECT_THROW(static_cast<void>(black_scholes_call_rho(input)), std::domain_error);
    }
}