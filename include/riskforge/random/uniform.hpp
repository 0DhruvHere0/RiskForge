#pragma once
#include <cstdint>
namespace riskforge::random{
    [[nodiscard]]
    double uniform_open01(
        std::uint32_t word0,
        std::uint32_t word1
    );
}