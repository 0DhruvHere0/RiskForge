#pragma once
#include <vector>
namespace riskforge::portfolio{
    [[nodiscard]]
    std::vector<double> calculate_portfolio_losses(
        const std::vector<std::vector<double>>& terminal_prices,
        const std::vector<double>& initial_prices,
        const std::vector<double>& weights
    );
}