#include "riskforge/backtesting/report_csv.hpp"
#include <gtest/gtest.h>
#include <string>
namespace{
    using riskforge::backtesting::BacktestReport;
    using riskforge::backtesting::VarBacktestResult;
    using riskforge::backtesting::backtest_report_to_csv;
    TEST(ReportCsvTest, SerializesBacktestReport){
        const BacktestReport report{
            VarBacktestResult{
                100u,
                5u,
                0.05
            },
            0.25,
            0.16
        };
        const std::string csv=backtest_report_to_csv(report);
        EXPECT_NE(
            csv.find(
                "observations,exceptions,exception_rate,maximum_drawdown,annualized_volatility"
            ),
            std::string::npos
        );
        EXPECT_NE(csv.find("100,5,0.050000000000000003"), std::string::npos);
    }
}