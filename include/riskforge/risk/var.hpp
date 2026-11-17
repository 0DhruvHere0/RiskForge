#pragma once
namespace riskforge::risk{
    [[nodiscard]]
    double lognormal_value_at_risk(
        double initial_price,
        double drift,
        double volatility,
        double time,
        double confidence_level
    );
}