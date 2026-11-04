#include "riskforge/risk/tail.hpp"
#include <array>
#include <gtest/gtest.h>
#include <span>
#include <stdexcept>
namespace{
    using riskforge::risk::aggregate_upper_tail;
    using riskforge::risk::TailSummary;
    TEST(TailTest, AggregatesUpperTail){
        const std::array<double, 5> losses{
            1.0,
            5.0,
            2.0,
            8.0,
            3.0
        };
        const TailSummary result= aggregate_upper_tail(losses, 0.4);
        EXPECT_DOUBLE_EQ(result.threshold, 5.0);
        EXPECT_DOUBLE_EQ(result.sum, 13.0);
        EXPECT_EQ(result.count, 2);
    }
    TEST(TailTest, SelectsAtLeastOneObservation){
        const std::array<double, 4> losses{
            2.0,
            4.0,
            6.0,
            8.0
        };
        const TailSummary result= aggregate_upper_tail(losses, 0.01);
        EXPECT_DOUBLE_EQ(result.threshold, 8.0);
        EXPECT_DOUBLE_EQ(result.sum, 8.0);
        EXPECT_EQ(result.count, 1);
    }
    TEST(TailTest, RejectsInvalidTailProbability){
        const std::array<double, 2> losses{
            1.0,
            2.0
        };
        EXPECT_THROW(
            aggregate_upper_tail(losses, 0.0),
            std::invalid_argument
        );
        EXPECT_THROW(
            aggregate_upper_tail(losses, 1.1),
            std::invalid_argument
        );
    }
}