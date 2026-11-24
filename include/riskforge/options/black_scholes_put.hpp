#pragma once
#include "riskforge/options/black_scholes.hpp"
namespace riskforge::options{
    [[nodiscard]]
    double black_scholes_put_price(const BlackScholesInput& input);
    [[nodiscard]]
    double black_scholes_put_delta(const BlackScholesInput& input);
}