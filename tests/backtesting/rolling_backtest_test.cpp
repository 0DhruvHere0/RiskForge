#include "riskforge/backtesting/rolling_backtest.hpp"
#include <gtest/gtest.h>
#include <vector>
#include <cmath>
namespace{
    using riskforge::backtesting::rolling_backtest_reports;
    TEST(RollingBacktestTest, CalculatesRollingReports){
        const std::vector<double> log_returns{
            0.01,
            -0.02,
            -0.08,
            -0.12,
            0.02
        };
        const auto reports=rolling_backtest_reports(
            log_returns,
            3u,
            0.08,
            252.0
        );
        ASSERT_EQ(reports.size(), 3u);
        EXPECT_EQ(
            reports[0].value_at_risk_backtest.observation_count,
            3u
        );
        EXPECT_EQ(
            reports[1].value_at_risk_backtest.observation_count,
            3u
        );
        EXPECT_EQ(
            reports[2].value_at_risk_backtest.observation_count,
            3u
        );
        EXPECT_TRUE(std::isfinite(reports[0].maximum_drawdown));
        EXPECT_TRUE(std::isfinite(reports[1].annualized_volatility));
    }
}