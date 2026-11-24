#pragma once
#include <cstdint>
namespace riskforge::random{
    [[nodiscard]]
    double student_t_sample(double degrees_of_freedom, std::uint32_t seed, std::uint64_t sample);
}