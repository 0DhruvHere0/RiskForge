#include "riskforge/backtesting/performance_metrics.hpp"
#include <gtest/gtest.h>
#include <limits>
#include <stdexcept>
#include <vector>
namespace{
    using riskforge::backtesting::calculate_performance_metrics;
    TEST(PerformanceMetricsValidationTest, RejectsEmptyReturns){
        const std::vector<double> log_returns;
        EXPECT_THROW(
            static_cast<void>(
                calculate_performance_metrics(log_returns, 252.0)
            ),
            std::invalid_argument
        );
    }
    TEST(PerformanceMetricsValidationTest, RejectsInvalidPeriodsPerYear){
        const std::vector<double> log_returns{
            0.01,
            0.02
        };
        EXPECT_THROW(
            static_cast<void>(
                calculate_performance_metrics(log_returns, 0.0)
            ),
            std::invalid_argument
        );
    }
    TEST(PerformanceMetricsValidationTest, RejectsNonFiniteReturns){
        const std::vector<double> log_returns{
            0.01,
            std::numeric_limits<double>::quiet_NaN()
        };
        EXPECT_THROW(
            static_cast<void>(
                calculate_performance_metrics(log_returns, 252.0)
            ),
            std::invalid_argument
        );
    }
}