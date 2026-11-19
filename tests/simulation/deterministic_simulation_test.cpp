#include "riskforge/random/normal.hpp"
#include "riskforge/random/philox.hpp"
#include "riskforge/random/uniform.hpp"
#include "riskforge/simulation/gbm.hpp"
#include <gtest/gtest.h>
#include <cstdint>
namespace{
    double generate_terminal_price(
        std::uint32_t seed,
        std::uint32_t sample
    ){
        const riskforge::random::Philox4x32_10::Key key{
            seed, seed^ 0x9E3779B9u
        };
        const riskforge::random::Philox4x32_10::Counter counter{
            seed,
            sample,
            0u,
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
        return riskforge::simulation::gbm_terminal_price(
            100.0,
            0.05,
            0.20,
            1.0,
            standard_normal
        );
    }
    TEST(DeterministicSimulationTest, SameSeedProducesSamePrice){
        const double first= generate_terminal_price(42u, 100u);
        const double second= generate_terminal_price(42u, 100u);
        EXPECT_DOUBLE_EQ(first, second);
    }
    TEST(DeterministicSimulationTest, DifferentSeedsProduceDifferentPrices){
        const double first= generate_terminal_price(42u, 100u);
        const double second= generate_terminal_price(43u, 100u);
        EXPECT_NE(first, second);
    }
}