#pragma once
#include "riskforge/risk/tail.hpp"
#include <cstddef>
namespace riskforge::risk{
    class AdaptiveTailAccumulator{
        public:
            AdaptiveTailAccumulator(
                std::size_t observation_count,
                double tail_probability
            );
            void add(double loss);
            [[nodiscard]]
            TailSummary finalize() const;
        private:
            std::size_t observation_count_;
            std::size_t tail_count_;
            std::size_t values_seen_;
            std::vector<double> largest_losses_;
    };
}