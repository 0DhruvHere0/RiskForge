#pragma once
#include "riskforge/options/black_scholes.hpp"
#include <vector>
namespace riskforge::options{
    [[nodiscard]]
    std::vector<double> build_call_volatility_surface(const BlackScholesInput& base_input, const std::vector<double>& strikes, const std::vector<double>& market_prices);
}