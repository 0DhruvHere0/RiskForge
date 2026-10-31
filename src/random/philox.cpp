#include "riskforge/random/philox.hpp"
#include <cstdint>
namespace riskforge::random{
    namespace{
        constexpr std::uint32_t kMultiplier0= 0xD2511F53u;
        constexpr std::uint32_t kMultiplier1= 0xCD9E8D57u;
        constexpr std::uint32_t kWeyl0= 0x9E3779B9u;
        constexpr std::uint32_t kWeyl1= 0xBB67AE85u;
        struct MultiplyResult{
            std::uint32_t high;
            std::uint32_t low;
        };
        [[nodiscard]]
        MultiplyResult multiply_high_low(
            std::uint32_t multiplier,
            std::uint32_t value
        ){
            const std::uint64_t product= static_cast<std::uint64_t>(multiplier) * static_cast<std::uint64_t>(value);
            return {
                static_cast<std::uint32_t>(product>>32), static_cast<std::uint32_t>(product)
            };
        }
    }
    Philox4x32_10::Block Philox4x32_10::generate(
        const Counter& counter,
        const Key& key
    ){
        Counter state= counter;
        Key round_key= key;
        for (int round=0; round<10; ++round){
            const MultiplyResult product0= multiply_high_low(kMultiplier0, state[0]);
            const MultiplyResult product1= multiply_high_low(kMultiplier1, state[2]);
            state= {
                product1.high ^ state[1] ^ round_key[0],
                product1.low,
                product0.high ^ state[3] ^ round_key[1],
                product0.low
            };
            round_key[0]+= kWeyl0;
            round_key[1]+= kWeyl1;
        }
        return state;
    }
}