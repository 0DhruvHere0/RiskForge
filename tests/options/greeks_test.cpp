#include "riskforge/options/greeks.hpp"
#include <gtest/gtest.h>
namespace{
    using riskforge::options::BlackScholesInput;
    using riskforge::options::black_scholes_call_gamma;
    using riskforge::options::black_scholes_call_rho;
    using riskforge::options::black_scholes_call_theta;
    using riskforge::options::black_scholes_call_vega;
    const BlackScholesInput input{
        100.0,
        100.0,
        0.05,
        0.20,
        1.0
    };
    TEST(GreeksTest, CalculatesGamma){
        EXPECT_NEAR(black_scholes_call_gamma(input), 0.018762017345846895, 1e-10);
    }
    TEST(GreeksTest, CalculatesVega){
        EXPECT_NEAR(black_scholes_call_vega(input), 37.52403469169379, 1e-10);
    }
    TEST(GreeksTest, CalculatesTheta){
        EXPECT_NEAR(black_scholes_call_theta(input), -6.414027546438197, 1e-10);
    }
    TEST(GreeksTest, CalculatesRho){
        EXPECT_NEAR(black_scholes_call_rho(input), 53.232481545376345, 1e-10);
    }
}