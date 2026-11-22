#include "riskforge/portfolio/portfolio.hpp"
#include <cmath>
#include <stdexcept>
#include <vector>
namespace riskforge::portfolio{
    std::vector<double> calculate_portfolio_losses(
        const std::vector<std::vector<double>>& terminal_prices,
        const std::vector<double>& initial_prices,
        const std::vector<double>& weights
    ){
        if (terminal_prices.empty()){
            throw std::invalid_argument("terminal prices must not be empty");
        }
        if (initial_prices.empty() || initial_prices.size()!=weights.size()){
            throw std::invalid_argument("initial prices and weights must have equal sizes");
        }
        const std::size_t asset_count= initial_prices.size();
        double initial_portfolio_value= 0.0;
        for (std::size_t asset=0; asset<asset_count; ++asset){
            if (!std::isfinite(initial_prices[asset]) || initial_prices[asset]<=0.0){
                throw std::invalid_argument("initial prices must be positive and finite");
            }
            if (!std::isfinite(weights[asset])){
                throw std::invalid_argument("weights must be finite");
            }
            initial_portfolio_value+= initial_prices[asset]*weights[asset];
        }
        std::vector<double> losses;
        losses.reserve(terminal_prices.size());
        for (const auto& path :terminal_prices){
            if (path.size()!=asset_count){
                throw std::invalid_argument("terminal price dimensions must match assets");
            }
            double terminal_portfolio_value= 0.0;
            for (std::size_t asset=0; asset<asset_count; ++asset){
                if (!std::isfinite(path[asset]) || path[asset]<=0.0){
                    throw std::invalid_argument("terminal prices must be positive and finite");
                }
                terminal_portfolio_value+= path[asset]*weights[asset];
            }
            losses.push_back(initial_portfolio_value-terminal_portfolio_value);
        }
        return losses;
    }
}