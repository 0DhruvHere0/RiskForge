#pragma once
namespace riskforge::risk{
    [[nodiscard]]
    double lognormal_expected_shortfall(
        double initial_price,
        double drift,
        double volatility,
        double time,
        double confidence_level
    );
}