#include "riskforge/portfolio/portfolio.hpp"
#include <gtest/gtest.h>
#include <stdexcept>
namespace{
    using riskforge::portfolio::
        calculate_portfolio_losses;
    TEST(PortfolioValidationTest, RejectsEmptyTerminalPrices){
        const std::vector<std::vector<double>> terminal_prices;
        const std::vector<double> initial_prices{100.0};
        const std::vector<double> weights{1.0};
        EXPECT_THROW(
            static_cast<void>(
                calculate_portfolio_losses(
                    terminal_prices,
                    initial_prices,
                    weights
                )
            ),
            std::invalid_argument
        );
    }
    TEST(PortfolioValidationTest, RejectsMismatchedWeights){
        const std::vector<std::vector<double>> terminal_prices{{110.0, 190.0}};
        const std::vector<double> initial_prices{100.0, 200.0};
        const std::vector<double> weights{1.0};
        EXPECT_THROW(
            static_cast<void>(
                calculate_portfolio_losses(
                    terminal_prices,
                    initial_prices,
                    weights
                )
            ),
            std::invalid_argument
        );
    }
    TEST(PortfolioValidationTest, RejectsMismatchedPathDimensions){
        const std::vector<std::vector<double>> terminal_prices{{110.0}};
        const std::vector<double> initial_prices{100.0, 200.0};
        const std::vector<double> weights{0.5, 0.5};
        EXPECT_THROW(
            static_cast<void>(
                calculate_portfolio_losses(
                    terminal_prices,
                    initial_prices,
                    weights
                )
            ),
            std::invalid_argument
        );
    }
}