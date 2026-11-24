#pragma once
#include "riskforge/options/black_scholes.hpp"
namespace riskforge::options{
    [[nodiscard]]
    double black_scholes_implied_volatility(const BlackScholesInput& input, double market_price);
}