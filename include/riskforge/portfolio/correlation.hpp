#pragma once
#include <vector>
namespace riskforge::portfolio{
    using Matrix= std::vector<std::vector<double>>;
    [[nodiscard]]
    Matrix cholesky_decompose(
        const Matrix& correlation_matrix
    );
}