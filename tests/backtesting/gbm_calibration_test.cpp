#include "riskforge/backtesting/gbm_calibration.hpp"
#include <gtest/gtest.h>
#include <vector>
namespace{
    using riskforge::backtesting::calibrate_gbm;
    TEST(GbmCalibrationTest, EstimatesAnnualizedParameters){
        const std::vector<double> log_returns{
            0.001,
            0.002,
            0.003
        };
        const auto result=calibrate_gbm(log_returns, 252.0);
        EXPECT_NEAR(result.annualized_volatility, 0.0158745078663875, 1e-12);
        EXPECT_NEAR(result.annualized_drift, 0.504126, 1e-12);
    }
}