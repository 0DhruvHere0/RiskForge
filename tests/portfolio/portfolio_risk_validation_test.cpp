#include "riskforge/portfolio/portfolio_risk.hpp"
#include <gtest/gtest.h>
#include <stdexcept>
namespace{
    using riskforge::portfolio::estimate_portfolio_risk;
    TEST(PortfolioRiskValidationTest, RejectsInvalidConfidence){
        const std::vector<std::vector<double>> terminal_prices{{110.0, 190.0}};
        const std::vector<double> initial_prices{100.0, 200.0};
        const std::vector<double> weights{0.5, 0.5};
        EXPECT_THROW(
            static_cast<void>(
                estimate_portfolio_risk(
                    terminal_prices,
                    initial_prices,
                    weights,
                    1.0
                )
            ),
            std::invalid_argument
        );
    }
    TEST(PortfolioRiskValidationTest, RejectsEmptyTerminalPrices){
        const std::vector<std::vector<double>> terminal_prices;
        const std::vector<double> initial_prices{100.0};
        const std::vector<double> weights{1.0};
        EXPECT_THROW(
            static_cast<void>(
                estimate_portfolio_risk(
                    terminal_prices,
                    initial_prices,
                    weights,
                    0.95
                )
            ),
            std::invalid_argument
        );
    }
    TEST(PortfolioRiskValidationTest, RejectsMismatchedWeights){
        const std::vector<std::vector<double>> terminal_prices{{110.0, 190.0}};
        const std::vector<double> initial_prices{100.0, 200.0};
        const std::vector<double> weights{1.0};
        EXPECT_THROW(
            static_cast<void>(
                estimate_portfolio_risk(
                    terminal_prices,
                    initial_prices,
                    weights,
                    0.95
                )
            ),
            std::invalid_argument
        );
    }
}