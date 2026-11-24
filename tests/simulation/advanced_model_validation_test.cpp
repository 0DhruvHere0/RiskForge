#include "riskforge/simulation/jump_diffusion.hpp"
#include "riskforge/simulation/stochastic_volatility.hpp"
#include "riskforge/simulation/student_t_gbm.hpp"
#include <gtest/gtest.h>
#include <stdexcept>
namespace{
    using riskforge::simulation::jump_diffusion_terminal_price;
    using riskforge::simulation::stochastic_volatility_terminal_price;
    using riskforge::simulation::student_t_gbm_terminal_price;
    TEST(AdvancedModelValidationTest, RejectsInvalidStudentTDegreesOfFreedom){
        EXPECT_THROW(static_cast<void>(student_t_gbm_terminal_price(100.0, 0.05, 0.20, 1.0, 2.0, 42u, 100u)), std::invalid_argument);
    }
    TEST(AdvancedModelValidationTest, RejectsInvalidStochasticVolatilitySteps){
        EXPECT_THROW(static_cast<void>(stochastic_volatility_terminal_price(100.0, 0.05, 0.04, 0.04, 2.0, 0.10, 1.0, 0, 42u, 100u)), std::invalid_argument);
    }
    TEST(AdvancedModelValidationTest, RejectsInvalidJumpIntensity){
        EXPECT_THROW(static_cast<void>(jump_diffusion_terminal_price(100.0, 0.05, 0.20, -0.1, -0.10, 0.20, 1.0, 42u, 100u)), std::invalid_argument);
    }
}