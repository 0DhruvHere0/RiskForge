#pragma once
#include "riskforge/options/black_scholes.hpp"
namespace riskforge::options{
    double black_scholes_put_gamma(const BlackScholesInput& input);
    double black_scholes_put_vega(const BlackScholesInput& input);
    double black_scholes_put_theta(const BlackScholesInput& input);
    double black_scholes_put_rho(const BlackScholesInput& input);
}