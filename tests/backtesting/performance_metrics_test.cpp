#include "riskforge/backtesting/performance_metrics.hpp"
#include <gtest/gtest.h>
#include <vector>
#include <cmath>
namespace{
    using riskforge::backtesting::calculate_performance_metrics;
    TEST(PerformanceMetricsTest, CalculatesPerformanceMetrics){
        const std::vector<double> log_returns{
            std::log(1.10),
            std::log(0.90)
        };
        const auto result=calculate_performance_metrics(
            log_returns,
            252.0
        );
        EXPECT_NEAR(result.total_log_return, std::log(0.99), 1e-12);
        EXPECT_NEAR(result.total_compounded_return, -0.01, 1e-12);
        EXPECT_NEAR(
            result.annualized_return,
            std::expm1(std::log(0.99)*126.0),
            1e-10
        );
    }
}