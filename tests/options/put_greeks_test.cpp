#include "riskforge/options/put_greeks.hpp"
#include <gtest/gtest.h>
namespace{
    using riskforge::options::BlackScholesInput;
    using riskforge::options::black_scholes_put_gamma;
    using riskforge::options::black_scholes_put_rho;
    using riskforge::options::black_scholes_put_theta;
    using riskforge::options::black_scholes_put_vega;
    const BlackScholesInput input{
        100.0,
        100.0,
        0.05,
        0.20,
        1.0
    };
    TEST(PutGreeksTest, CalculatesGamma){
        EXPECT_NEAR(black_scholes_put_gamma(input), 0.018762017345846895, 1e-10);
    }
    TEST(PutGreeksTest, CalculatesVega){
        EXPECT_NEAR(black_scholes_put_vega(input), 37.52403469169379, 1e-10);
    }
    TEST(PutGreeksTest, CalculatesTheta){
        EXPECT_NEAR(black_scholes_put_theta(input), -1.6578804239346258, 1e-10);
    }
    TEST(PutGreeksTest, CalculatesRho){
        EXPECT_NEAR(black_scholes_put_rho(input), -41.890460904695054, 1e-10);
    }
}