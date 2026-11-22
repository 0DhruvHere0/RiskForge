#include "riskforge/portfolio/portfolio_risk.hpp"
#include <gtest/gtest.h>
namespace{
    using riskforge::portfolio::
        estimate_portfolio_risk;
    TEST(PortfolioRiskTest, CalculatesVaRAndExpectedShortfall){
        const std::vector<std::vector<double>> terminal_prices{
            {110.0, 190.0},
            {90.0, 180.0},
            {80.0, 210.0},
            {120.0, 160.0}
        };
        const std::vector<double> initial_prices{100.0, 200.0};
        const std::vector<double> weights{0.5, 0.5};
        const auto result=
            estimate_portfolio_risk(
                terminal_prices,
                initial_prices,
                weights,
                0.5
            );
        EXPECT_NEAR(result.value_at_risk, 10.0, 1e-12);
        EXPECT_NEAR(
            result.expected_shortfall,
            12.5,
            1e-12
        );
    }
    TEST(PortfolioRiskTest, ExpectedShortfallIsAtLeastVaR){
        const std::vector<std::vector<double>> terminal_prices{
            {110.0, 190.0},
            {90.0, 180.0},
            {80.0, 210.0},
            {120.0, 160.0}
        };
        const std::vector<double> initial_prices{100.0, 200.0};
        const std::vector<double> weights{0.5, 0.5};
        const auto result=
            estimate_portfolio_risk(
                terminal_prices,
                initial_prices,
                weights,
                0.5
            );
        EXPECT_GE(
            result.expected_shortfall,
            result.value_at_risk
        );
    }
}