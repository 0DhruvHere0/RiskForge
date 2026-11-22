#include "riskforge/portfolio/correlation.hpp"
#include <cmath>
#include <stdexcept>
namespace riskforge::portfolio{
    Matrix cholesky_decompose(
        const Matrix& correlation_matrix
    ){
        if (correlation_matrix.empty()){
            throw std::invalid_argument("correlation matrix must not be empty");
        }
        const std::size_t dimension= correlation_matrix.size();
        for (const auto& row : correlation_matrix){
            if (row.size()!=dimension){
                throw std::invalid_argument("correlation matrix must be square");
            }
            for (const double value : row){
                if (!std::isfinite(value)){
                    throw std::invalid_argument("correlation matrix must be finite");
                }
            }
        }
        for (std::size_t row=0; row<dimension; ++row){
            for (std::size_t column=row+1; column<dimension; ++column){
                if (std::abs(correlation_matrix[row][column]- correlation_matrix[column][row])>1e-12){
                    throw std::invalid_argument("correlation matrix must be symmetric");
                }
            }
        }
        Matrix lower(dimension, std::vector<double>(dimension, 0.0));
        for (std::size_t row=0; row<dimension; ++row){
            for (std::size_t column=0;
                column<=row;
                ++column){
                double sum= correlation_matrix[row][column];
                for (std::size_t index=0; index<column; ++index){
                    sum-= lower[row][index]* lower[column][index];
                }
                if (row==column){
                    if (sum<=0.0){
                        throw std::invalid_argument("correlation matrix must be positive definite");
                    }
                    lower[row][column]= std::sqrt(sum);
                }
                else{
                    lower[row][column]= sum/lower[column][column];
                }
            }
        }
        return lower;
    }
}