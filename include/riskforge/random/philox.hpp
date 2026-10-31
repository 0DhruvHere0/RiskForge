#pragma once
#include <array>
#include <cstdint>
namespace riskforge::random{
    class Philox4x32_10{
        public:
            using Counter= std::array<std::uint32_t, 4>;
            using Key= std::array<std::uint32_t, 2>;
            using Block= std::array<std::uint32_t, 4>;
            [[nodiscard]]
            static Block generate(const Counter& counter, const Key& key);
    };
}