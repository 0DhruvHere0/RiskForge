#include "riskforge/random/normal.hpp"
#include "riskforge/random/philox.hpp"
#include "riskforge/random/uniform.hpp"
#include "riskforge/risk/var.hpp"
#include "riskforge/simulation/gbm.hpp"
#include <gtest/gtest.h>
#include <cstddef>
#include <cstdint>
namespace{
    TEST(GBMCoverageTest, EmpiricalVaRExceedanceIsNearFivePercent){
        constexpr double inital_price= 100.0;
        constexpr double drift= 0.05;
        constexpr double volatility= 0.20;
        constexpr double time= 1.0;
        constexpr double confidence_level= 0.95;
        constexpr std::size_t seed_count= 200;
        constexpr std::size_t samples_per_seed= 10'000;
        const double true_value_at_risk= riskforge::risk::lognormal_value_at_risk(
            inital_price,
            drift,
            volatility,
            time,
            confidence_level
        );
        std::size_t exceedances= 0;
        const std::size_t total_samples= seed_count* samples_per_seed;
        for (std::uint32_t seed=0; seed<seed_count; ++seed){
            const riskforge::random::Philox4x32_10::Key key{
                seed, seed ^ 0x9E3779B9u
            };
            for (std::uint32_t sample=0; sample<samples_per_seed; ++sample){
                const riskforge::random::Philox4x32_10::Counter counter{
                    sample,
                    0u,
                    seed,
                    0u
                };
                const auto block= riskforge::random::Philox4x32_10::generate(
                    counter,
                    key
                );
                const double uniform= riskforge::random::uniform_open01(
                    block[0],
                    block[1]
                );
                const double standard_normal= riskforge::random::normal_ppf(uniform);
                const double terminal_price= riskforge::simulation::gbm_terminal_price(
                    inital_price,
                    drift,
                    volatility,
                    time,
                    standard_normal
                );
                const double loss= inital_price- terminal_price;
                if (loss>= true_value_at_risk){
                    ++exceedances;
                }
            }
        }
        const double observed_exceedance_rate=
            static_cast<double>(exceedances)/ static_cast<double>(total_samples);
        EXPECT_GE(observed_exceedance_rate, 0.045);
    }
}