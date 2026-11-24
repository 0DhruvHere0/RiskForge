#include "riskforge/backtesting/risk_comparison.hpp"
#include <gtest/gtest.h>
#include <limits>
#include <stdexcept>
namespace{
    using riskforge::backtesting::HistoricalRiskResult;
    using riskforge::backtesting::compare_risk_estimates;
    TEST(RiskComparisonValidationTest, RejectsNonFiniteHistoricalRisk){
        const HistoricalRiskResult historical{
            std::numeric_limits<double>::quiet_NaN(),
            0.15
        };
        const HistoricalRiskResult simulated{
            0.12,
            0.18
        };
        EXPECT_THROW(
            static_cast<void>(
                compare_risk_estimates(historical, simulated)
            ),
            std::invalid_argument
        );
    }
    TEST(RiskComparisonValidationTest, RejectsNonFiniteSimulatedRisk){
        const HistoricalRiskResult historical{
            0.10,
            0.15
        };
        const HistoricalRiskResult simulated{
            0.12,
            std::numeric_limits<double>::infinity()
        };
        EXPECT_THROW(
            static_cast<void>(
                compare_risk_estimates(historical, simulated)
            ),
            std::invalid_argument
        );
    }
}