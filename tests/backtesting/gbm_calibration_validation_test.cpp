#include "riskforge/backtesting/gbm_calibration.hpp"
#include <gtest/gtest.h>
#include <limits>
#include <stdexcept>
#include <vector>
namespace{
    using riskforge::backtesting::calibrate_gbm;
    TEST(GbmCalibrationValidationTest, RejectsTooFewReturns){
        const std::vector<double> log_returns{0.001};
        EXPECT_THROW(
            static_cast<void>(
                calibrate_gbm(log_returns, 252.0)
            ),
            std::invalid_argument
        );
    }
    TEST(GbmCalibrationValidationTest, RejectsInvalidPeriodsPerYear){
        const std::vector<double> log_returns{
            0.001,
            0.002
        };
        EXPECT_THROW(
            static_cast<void>(
                calibrate_gbm(log_returns, 0.0)
            ),
            std::invalid_argument
        );
    }
    TEST(GbmCalibrationValidationTest, RejectsNonFiniteReturns){
        const std::vector<double> log_returns{
            0.001,
            std::numeric_limits<double>::infinity()
        };
        EXPECT_THROW(
            static_cast<void>(
                calibrate_gbm(log_returns, 252.0)
            ),
            std::invalid_argument
        );
    }
}