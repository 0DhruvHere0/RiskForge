#include "riskforge/options/black_scholes.hpp"
#include <algorithm>
#include <cmath>
#include <stdexcept>
namespace riskforge::options{
    namespace{
        void validate_input(const BlackScholesInput& input){
            if (!std::isfinite(input.spot) || input.spot<=0.0){
                throw std::invalid_argument("spot must be positive and finite");
            }
            if (!std::isfinite(input.strike) || input.strike<=0.0){
                throw std::invalid_argument("strike must be positive and finite");
            }
            if (!std::isfinite(input.risk_free_rate)){
                throw std::invalid_argument("risk free rate must be finite");
            }
            if (!std::isfinite(input.volatility) || input.volatility<0.0){
                throw std::invalid_argument("volatility must be non-negative and finite");
            }
            if (!std::isfinite(input.time) || input.time<0.0){
                throw std::invalid_argument("time must be non-negative and finite");
            }
        }
        double normal_cdf(double value){
            return 0.5*std::erfc(-value/std::sqrt(2.0));
        }
    }
    double black_scholes_call_price(const BlackScholesInput& input){
        validate_input(input);
        if (input.time==0.0){
            return std::max(input.spot-input.strike, 0.0);
        }
        if (input.volatility==0.0){
            const double discounted_strike=input.strike*std::exp(-input.risk_free_rate*input.time);
            return std::max(input.spot-discounted_strike, 0.0);
        }
        const double volatility_time=input.volatility*std::sqrt(input.time);
        const double d1=(std::log(input.spot/input.strike)+(input.risk_free_rate+0.5*input.volatility*input.volatility)*input.time)/volatility_time;
        const double d2=d1-volatility_time;
        return input.spot*normal_cdf(d1)-input.strike*std::exp(-input.risk_free_rate*input.time)*normal_cdf(d2);
    }
    double black_scholes_call_delta(const BlackScholesInput& input){
        validate_input(input);
        if (input.time==0.0){
            if (input.spot>input.strike){
                return 1.0;
            }
            if (input.spot<input.strike){
                return 0.0;
            }
            return 0.5;
        }
        if (input.volatility==0.0){
            const double discounted_strike=input.strike*std::exp(-input.risk_free_rate*input.time);
            return input.spot>discounted_strike ? 1.0 : 0.0;
        }
        const double d1=(std::log(input.spot/input.strike)+(input.risk_free_rate+0.5*input.volatility*input.volatility)*input.time)/(input.volatility*std::sqrt(input.time));
        return normal_cdf(d1);
    }
}