#include "riskforge/options/black_scholes_put.hpp"
#include <cmath>
namespace riskforge::options{
    double black_scholes_put_price(const BlackScholesInput& input){
        const double call_price=black_scholes_call_price(input);
        const double discounted_strike=input.strike*std::exp(-input.risk_free_rate*input.time);
        return call_price-input.spot+discounted_strike;
    }
    double black_scholes_put_delta(const BlackScholesInput& input){
        return black_scholes_call_delta(input)-1.0;
    }
}