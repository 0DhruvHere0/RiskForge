#pragma once
namespace riskforge::options{
    struct BlackScholesInput{
        double spot;
        double strike;
        double risk_free_rate;
        double volatility;
        double time;
    };
    [[nodiscard]]
    double black_scholes_call_price(const BlackScholesInput& input);
    [[nodiscard]]
    double black_scholes_call_delta(const BlackScholesInput& input);
}