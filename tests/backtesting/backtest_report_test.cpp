#include "riskforge/backtesting/backtest_report.hpp"
#include <gtest/gtest.h>
#include <vector>
namespace{
    using riskforge::backtesting::create_backtest_report;
    TEST(BacktestReportTest, CombinesBacktestMetrics){
        const std::vector<double> log_returns{
            0.01,
            -0.03,
            -0.08,
            -0.12,
            0.02
        };
        const auto report=create_backtest_report(
            log_returns,
            0.08,
            252.0
        );
        EXPECT_EQ(report.value_at_risk_backtest.observation_count, 5u);
        EXPECT_EQ(report.value_at_risk_backtest.exception_count, 1u);
        EXPECT_DOUBLE_EQ(report.value_at_risk_backtest.exception_rate, 0.2);
        EXPECT_GT(report.maximum_drawdown, 0.0);
        EXPECT_GT(report.annualized_volatility, 0.0);
    }
}