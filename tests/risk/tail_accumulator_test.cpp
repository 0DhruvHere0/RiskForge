#include "riskforge/risk/tail_accumulator.hpp"
#include <gtest/gtest.h>
namespace{
    using riskforge::risk::AdaptiveTailAccumulator;
    TEST(AdaptiveTailAccumulatorTest, AggregatesLargestLosses){
        AdaptiveTailAccumulator accumulator(5, 0.4);
        accumulator.add(1.0);
        accumulator.add(5.0);
        accumulator.add(2.0);
        accumulator.add(8.0);
        accumulator.add(3.0);
        const auto summary= accumulator.finalize();
        EXPECT_DOUBLE_EQ(summary.threshold, 5.0);
        EXPECT_DOUBLE_EQ(summary.sum, 13.0);
        EXPECT_EQ(summary.count, 2u);
    }
    TEST(AdaptiveTailAccumulatorTest, ProducesSameSummaryRegardlessOfOrder){
        AdaptiveTailAccumulator first(5, 0.4);
        AdaptiveTailAccumulator second(5, 0.4);
        for (const double value: {1.0, 5.0, 2.0, 8.0, 3.0}){
            first.add(value);
        }
        for (const double value: {3.0, 8.0, 2.0, 5.0, 1.0}){
            second.add(value);
        }
        const auto first_summary= first.finalize();
        const auto second_summary= second.finalize();
        EXPECT_DOUBLE_EQ(
            first_summary.threshold,
            second_summary.threshold
        );
        EXPECT_DOUBLE_EQ(
            first_summary.sum,
            second_summary.sum
        );
        EXPECT_EQ(
            first_summary.count,
            second_summary.count
        );
    }
}