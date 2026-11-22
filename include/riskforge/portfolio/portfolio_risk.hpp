#pragma once
#include <vector>
namespace riskforge::portfolio{
    struct PortfolioRiskResult{
        double value_at_risk;
        double expected_shortfall;
    };
    [[nodiscard]]
    PortfolioRiskResult estimate_portfolio_risk(
        const std::vector<std::vector<double>>& terminal_prices,
        const std::vector<double>& initial_prices,
        const std::vector<double>& weights,
        double confidence_level
    );
}