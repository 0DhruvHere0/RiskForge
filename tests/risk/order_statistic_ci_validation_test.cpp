#include "riskforge/risk/order_statistic_ci.hpp"
#include <gtest/gtest.h>
#include <limits>
#include <stdexcept>
#include <vector>
namespace {
    using riskforge::risk::order_statistic_quantile_ci;
    TEST(OrderStatisticCiValidationTest, RejectsEmptySamples){
        const std::vector<double> samples;
        EXPECT_THROW(
            static_cast<void>(
                order_statistic_quantile_ci(
                    samples,
                    0.95,
                    0.95
                )
            ),
            std::invalid_argument
        );
    }
    TEST(OrderStatisticCiValidationTest, RejectsInvalidQuantile){
        const std::vector<double> samples{
            1.0, 2.0, 3.0
        };
        EXPECT_THROW(
            static_cast<void>(
                order_statistic_quantile_ci(
                    samples,
                    1.0,
                    0.95
                )
            ),
            std::invalid_argument
        );
    }
    TEST(OrderStatisticCiValidationTest, RejectsInvalidConfidence){
        const std::vector<double> samples{
            1.0, 2.0, 3.0
        };
        EXPECT_THROW(
            static_cast<void>(
                order_statistic_quantile_ci(
                    samples,
                    0.95,
                    0.0
                )
            ),
            std::invalid_argument
        );
    }
    TEST(OrderStatisticCiValidationTest, RejectsNonFiniteSamples){
        const std::vector<double> samples{
            1.0,
            std::numeric_limits<double>::infinity(),
            3.0
        };
        EXPECT_THROW(
            static_cast<void>(
                order_statistic_quantile_ci(
                    samples,
                    0.95,
                    0.95
                )
            ),
            std::invalid_argument
        );
    }
}