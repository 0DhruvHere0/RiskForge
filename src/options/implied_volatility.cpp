#include "riskforge/options/implied_volatility.hpp"
#include <cmath>
#include <stdexcept>
#include <algorithm>
namespace riskforge::options{
    double black_scholes_implied_volatility(const BlackScholesInput& input, double market_price){
        if (!std::isfinite(market_price) || market_price<0.0){
            throw std::invalid_argument("market price must be non-negative and finite");
        }
        if (input.time<=0.0){
            throw std::domain_error("time must be positive");
        }
        const double discounted_strike=input.strike*std::exp(-input.risk_free_rate*input.time);
        const double intrinsic_value=std::max(input.spot-discounted_strike, 0.0);
        if (market_price<intrinsic_value || market_price>=input.spot){
            throw std::invalid_argument("market price is outside valid call bounds");
        }
        double lower_bound=1e-8;
        double upper_bound=5.0;
        for (int iteration=0; iteration<100; ++iteration){
            const double volatility=0.5*(lower_bound+upper_bound);
            BlackScholesInput trial=input;
            trial.volatility=volatility;
            const double price=black_scholes_call_price(trial);
            if (price>market_price){
                upper_bound=volatility;
            }
            else{
                lower_bound=volatility;
            }
        }
        return 0.5*(lower_bound+upper_bound);
    }
}