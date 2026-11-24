#pragma once
#include "riskforge/options/black_scholes.hpp"
namespace riskforge::options{
    [[nodiscard]]
    double black_scholes_call_gamma(const BlackScholesInput& input);
    [[nodiscard]]
    double black_scholes_call_vega(const BlackScholesInput& input);
    [[nodiscard]]
    double black_scholes_call_theta(const BlackScholesInput& input);
    [[nodiscard]]
    double black_scholes_call_rho(const BlackScholesInput& input);
}