#include "riskforge/options/volatility_surface.hpp"
#include <gtest/gtest.h>
#include <stdexcept>
namespace{
    using riskforge::options::BlackScholesInput;
    using riskforge::options::build_call_volatility_surface;
    TEST(VolatilitySurfaceValidationTest, RejectsEmptyInputs){
        const BlackScholesInput input{
            100.0,
            100.0,
            0.05,
            0.0,
            1.0
        };
        EXPECT_THROW(static_cast<void>(build_call_volatility_surface(input, {}, {})), std::invalid_argument);
    }
    TEST(VolatilitySurfaceValidationTest, RejectsMismatchedInputs){
        const BlackScholesInput input{
            100.0,
            100.0,
            0.05,
            0.0,
            1.0
        };
        EXPECT_THROW(static_cast<void>(build_call_volatility_surface(input, {90.0, 100.0}, {10.0})), std::invalid_argument);
    }
    TEST(VolatilitySurfaceValidationTest, RejectsInvalidStrike){
        const BlackScholesInput input{
            100.0,
            100.0,
            0.05,
            0.0,
            1.0
        };
        EXPECT_THROW(static_cast<void>(build_call_volatility_surface(input, {0.0}, {10.0})), std::invalid_argument);
    }
}