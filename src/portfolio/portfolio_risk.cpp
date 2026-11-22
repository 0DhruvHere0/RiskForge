#include "riskforge/portfolio/portfolio_risk.hpp"
#include "riskforge/portfolio/portfolio.hpp"
#include "riskforge/risk/tail_accumulator.hpp"
#include <cmath>
#include <stdexcept>
namespace riskforge::portfolio{
    PortfolioRiskResult estimate_portfolio_risk(
        const std::vector<std::vector<double>>& terminal_prices,
        const std::vector<double>& initial_prices,
        const std::vector<double>& weights,
        double confidence_level
    ){
        if (!std::isfinite(confidence_level) || confidence_level<=0.0 || confidence_level>=1.0){
            throw std::invalid_argument("confidence_level must be between 0 and 1");
        }
        const auto losses=
            calculate_portfolio_losses(
                terminal_prices,
                initial_prices,
                weights
            );
        riskforge::risk::AdaptiveTailAccumulator accumulator(
            losses.size(),
            1.0-confidence_level
        );
        for (const double loss : losses){
            accumulator.add(loss);
        }
        const auto summary= accumulator.finalize();
        return PortfolioRiskResult{
            summary.threshold,
            summary.sum/
                static_cast<double>(summary.count)
        };
    }
}