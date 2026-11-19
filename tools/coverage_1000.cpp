#include "riskforge/risk/order_statistic_ci.hpp"
#include "riskforge/risk/var.hpp"
#include "riskforge/simulation/monte_carlo.hpp"
#include <array>
#include <cstdint>
#include <iostream>
#include <vector>
namespace{
    constexpr std::size_t seed_count= 1000;
    constexpr std::size_t sample_count= 100'000;
    constexpr std::uint32_t make_seed(
        std::size_t index
    ){
        return 0x10000000u+
            static_cast<std::uint32_t>(
                index*0x9E3779B9u
            );
    }
}
int main(){
    const riskforge::simulation::GbmSimulationConfig base_config{
        100.0,
        0.05,
        0.20,
        1.0,
        sample_count,
        0u
    };
    const double true_value_at_risk=
        riskforge::risk::lognormal_value_at_risk(
            base_config.initial_price,
            base_config.drift,
            base_config.volatility,
            base_config.time,
            0.95
        );
    std::size_t covered_seeds= 0;
    for (std::size_t index= 0;
         index< seed_count;
         ++index){
        auto config= base_config;
        config.seed= make_seed(index);
        const auto terminal_prices=
            riskforge::simulation::
            simulate_gbm_terminal_prices(config);
        std::vector<double> losses;
        losses.reserve(terminal_prices.size());
        for (const double terminal_price :
             terminal_prices){
            losses.push_back(
                config.initial_price-terminal_price
            );
        }
        const auto interval=
            riskforge::risk::
            order_statistic_quantile_ci(
                losses,
                0.95,
                0.95
            );
        if (true_value_at_risk>= interval.lower_value &&
            true_value_at_risk<= interval.upper_value){
            ++covered_seeds;
        }
    }
    const double observed_coverage=
        static_cast<double>(covered_seeds)/
        static_cast<double>(seed_count);
    std::cout
        << "covered_seeds=" << covered_seeds
        << '\n'
        << "total_seeds=" << seed_count
        << '\n'
        << "coverage=" << observed_coverage
        << '\n';
    return 0;
}