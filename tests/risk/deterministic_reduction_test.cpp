#include "riskforge/risk/tail.hpp"
#include <gtest/gtest.h>
#include <array>
namespace {
using riskforge::risk::aggregate_upper_tail;
TEST(DeterministicReductionTest, InputOrderDoesNotChangeTailSummary) {
    const std::array<double, 6> losses_a{
        12.0, 4.0, 19.0, 7.0, 15.0, 2.0
    };
    const std::array<double, 6> losses_b{
        2.0, 15.0, 7.0, 19.0, 4.0, 12.0
    };
    const auto summary_a =aggregate_upper_tail(losses_a, 0.5);
    const auto summary_b =aggregate_upper_tail(losses_b, 0.5);
    EXPECT_DOUBLE_EQ(summary_a.threshold, summary_b.threshold);
    EXPECT_DOUBLE_EQ(summary_a.sum, summary_b.sum);
    EXPECT_EQ(summary_a.count, summary_b.count);
}
TEST(DeterministicReductionTest, RepeatedReductionProducesSameResult) {
    const std::array<double, 5> losses{
        10.0, 30.0, 20.0, 40.0, 50.0
    };
    const auto first =
        aggregate_upper_tail(losses, 0.4);
    const auto second = aggregate_upper_tail(losses, 0.4);
    EXPECT_DOUBLE_EQ(first.threshold, second.threshold);
    EXPECT_DOUBLE_EQ(first.sum, second.sum);
    EXPECT_EQ(first.count, second.count);
    }
}