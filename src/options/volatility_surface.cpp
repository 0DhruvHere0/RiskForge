#include "riskforge/options/volatility_surface.hpp"
#include "riskforge/options/implied_volatility.hpp"
#include <cmath>
#include <stdexcept>
namespace riskforge::options{
    std::vector<double> build_call_volatility_surface(const BlackScholesInput& base_input, const std::vector<double>& strikes, const std::vector<double>& market_prices){
        if (strikes.empty() || strikes.size()!=market_prices.size()){
            throw std::invalid_argument("strikes and market prices must have equal non-empty sizes");
        }
        std::vector<double> volatilities;
        volatilities.reserve(strikes.size());
        for (std::size_t index=0; index<strikes.size(); ++index){
            if (!std::isfinite(strikes[index]) || strikes[index]<=0.0){
                throw std::invalid_argument("strikes must be positive and finite");
            }
            BlackScholesInput input=base_input;
            input.strike=strikes[index];
            input.volatility=0.0;
            volatilities.push_back(black_scholes_implied_volatility(input, market_prices[index]));
        }
        return volatilities;
    }
}