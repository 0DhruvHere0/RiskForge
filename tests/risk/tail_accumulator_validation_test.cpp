#include "riskforge/risk/tail_accumulator.hpp"
#include <gtest/gtest.h>
#include <stdexcept>
#include <limits>
namespace{
    using riskforge::risk::AdaptiveTailAccumulator;
    TEST(AdaptiveTailAccumulatorValidationTest, RejectsZeroObservationCount){
        EXPECT_THROW(
            AdaptiveTailAccumulator(0, 0.4),
            std::invalid_argument
        );
    }
    TEST(AdaptiveTailAccumulatorValidationTest, RejectsIncompleteInput){
        AdaptiveTailAccumulator accumulator(3, 0.4);
        accumulator.add(10.0);
        EXPECT_THROW(
            static_cast<void>(
                accumulator.finalize()
            ),
            std::logic_error
        );
    }
    TEST(AdaptiveTailAccumulatorValidationTest, RejectsTooManyObservations){
        AdaptiveTailAccumulator accumulator(2, 0.5);
        accumulator.add(10.0);
        accumulator.add(20.0);
        EXPECT_THROW(
            accumulator.add(30.0),
            std::logic_error
        );
    }
    TEST(AdaptiveTailAccumulatorValidationTest, RejectsNonFiniteLoss){
        AdaptiveTailAccumulator accumulator(2, 0.5);
        EXPECT_THROW(
            accumulator.add(std::numeric_limits<double>::infinity()),
            std::invalid_argument
        );
    }
}