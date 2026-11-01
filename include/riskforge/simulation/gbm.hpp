#pragma once
namespace riskforge::simulation{
    [[nodiscard]]
    double gbm_terminal_price(
        double initial_price,
        double drift,
        double volatility,
        double time,
        double standard_normal
    );
}