#include "riskforge/options/put_greeks.hpp"
#include "riskforge/options/greeks.hpp"
#include <cmath>
namespace riskforge::options{
    double black_scholes_put_gamma(const BlackScholesInput& input){
        return black_scholes_call_gamma(input);
    }
    double black_scholes_put_vega(const BlackScholesInput& input){
        return black_scholes_call_vega(input);
    }
    double black_scholes_put_theta(const BlackScholesInput& input){
        return black_scholes_call_theta(input)+input.risk_free_rate*input.strike*std::exp(-input.risk_free_rate*input.time);
    }
    double black_scholes_put_rho(const BlackScholesInput& input){
        return black_scholes_call_rho(input)-input.strike*input.time*std::exp(-input.risk_free_rate*input.time);
    }
}