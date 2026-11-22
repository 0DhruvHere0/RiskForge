#include "riskforge/portfolio/portfolio.hpp"
#include <gtest/gtest.h>
namespace{
    using riskforge::portfolio::
        calculate_portfolio_losses;
    TEST(PortfolioTest, CalculatesWeightedPortfolioLosses){
        const std::vector<std::vector<double>> terminal_prices{
            {110.0, 190.0},
            {90.0, 180.0}
        };
        const std::vector<double> initial_prices{100.0, 200.0};
        const std::vector<double> weights{0.5, 0.5};
        const auto losses=calculate_portfolio_losses(
            terminal_prices,
            initial_prices,
            weights
        );
        ASSERT_EQ(losses.size(), 2u);
        EXPECT_NEAR(losses[0], 0.0, 1e-12);
        EXPECT_NEAR(losses[1], 15.0, 1e-12);
    }
    TEST(PortfolioTest, SupportsUnequalWeights){
        const std::vector<std::vector<double>> terminal_prices{{110.0, 190.0}};
        const std::vector<double> initial_prices{100.0, 200.0};
        const std::vector<double> weights{1.0, 0.0};
        const auto losses=calculate_portfolio_losses(
            terminal_prices,
            initial_prices,
            weights
        );
        ASSERT_EQ(losses.size(), 1u);
        EXPECT_NEAR(losses[0], -10.0, 1e-12);
    }
}