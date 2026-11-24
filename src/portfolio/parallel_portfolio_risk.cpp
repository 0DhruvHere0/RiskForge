#include "riskforge/portfolio/parallel_portfolio_risk.hpp"
#include "riskforge/portfolio/parallel_multi_asset_gbm.hpp"
#include "riskforge/portfolio/portfolio.hpp"
#include "riskforge/risk/tail_accumulator.hpp"
#include <cmath>
#include <stdexcept>
namespace riskforge::portfolio{
    PortfolioRiskResult estimate_parallel_portfolio_risk(
        const MultiAssetGbmConfig& config,
        const std::vector<double>& weights,
        double confidence_level,
        std::size_t worker_count
    ){
        if (!std::isfinite(confidence_level) ||
            confidence_level<=0.0 ||
            confidence_level>=1.0){
            throw std::invalid_argument(
                "confidence_level must be between 0 and 1"
            );
        }
        if (worker_count==0){
            throw std::invalid_argument(
                "worker_count must be greater than zero"
            );
        }
        const auto terminal_prices=
            simulate_multi_asset_gbm_terminal_prices_parallel(
                config,
                worker_count
            );
        const auto losses=
            calculate_portfolio_losses(
                terminal_prices,
                config.initial_prices,
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