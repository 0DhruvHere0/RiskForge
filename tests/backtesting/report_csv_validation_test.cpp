#include "riskforge/backtesting/report_csv.hpp"
#include <gtest/gtest.h>
#include <limits>
#include <stdexcept>
namespace{
    using riskforge::backtesting::BacktestReport;
    using riskforge::backtesting::VarBacktestResult;
    using riskforge::backtesting::backtest_report_to_csv;
    TEST(ReportCsvValidationTest, RejectsNonFiniteReportValues){
        const BacktestReport report{
            VarBacktestResult{
                100u,
                5u,
                std::numeric_limits<double>::quiet_NaN()
            },
            0.25,
            0.16
        };
        EXPECT_THROW(
            static_cast<void>(backtest_report_to_csv(report)),
            std::invalid_argument
        );
    }
}