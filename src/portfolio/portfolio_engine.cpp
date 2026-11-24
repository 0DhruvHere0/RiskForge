#include "riskforge/portfolio/portfolio_engine.hpp"
#include "riskforge/portfolio/parallel_portfolio_risk.hpp"
namespace riskforge::portfolio{
    PortfolioRiskResult run_portfolio_risk(
        const PortfolioEngineConfig& config
    ){
        return estimate_parallel_portfolio_risk(
            config.simulation,
            config.weights,
            config.confidence_level,
            config.worker_count
        );
    }
}