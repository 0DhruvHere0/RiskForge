#include "riskforge/simulation/jump_diffusion.hpp"
#include "riskforge/simulation/stochastic_volatility.hpp"
#include "riskforge/simulation/student_t_gbm.hpp"
#include <gtest/gtest.h>
#include <cmath>
namespace{
    using riskforge::simulation::jump_diffusion_terminal_price;
    using riskforge::simulation::stochastic_volatility_terminal_price;
    using riskforge::simulation::student_t_gbm_terminal_price;
    TEST(AdvancedModelConsistencyTest, ModelsProduceFinitePrices){
        const double student_t=student_t_gbm_terminal_price(100.0, 0.05, 0.20, 1.0, 8.0, 42u, 100u);
        const double stochastic_volatility=stochastic_volatility_terminal_price(100.0, 0.05, 0.04, 0.04, 2.0, 0.10, 1.0, 100, 42u, 100u);
        const double jump_diffusion=jump_diffusion_terminal_price(100.0, 0.05, 0.20, 0.4, -0.10, 0.20, 1.0, 42u, 100u);
        EXPECT_TRUE(std::isfinite(student_t));
        EXPECT_TRUE(std::isfinite(stochastic_volatility));
        EXPECT_TRUE(std::isfinite(jump_diffusion));
        EXPECT_GT(student_t, 0.0);
        EXPECT_GT(stochastic_volatility, 0.0);
        EXPECT_GT(jump_diffusion, 0.0);
    }
    TEST(AdvancedModelConsistencyTest, ZeroJumpIntensityProducesDeterministicGrowth){
        const double result=jump_diffusion_terminal_price(100.0, 0.05, 0.0, 0.0, 0.0, 0.0, 1.0, 42u, 100u);
        EXPECT_NEAR(result, 105.12710963760242, 1e-12);
    }
}