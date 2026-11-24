#pragma once
#include <span>
namespace riskforge::backtesting{
    struct GbmCalibrationResult{
        double annualized_drift;
        double annualized_volatility;
    };
    [[nodiscard]]
    GbmCalibrationResult calibrate_gbm(
        std::span<const double> log_returns,
        double periods_per_year
    );
}