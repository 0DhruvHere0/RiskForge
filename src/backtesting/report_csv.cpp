#include "riskforge/backtesting/report_csv.hpp"
#include <cmath>
#include <iomanip>
#include <sstream>
#include <stdexcept>
namespace riskforge::backtesting{
    std::string backtest_report_to_csv(const BacktestReport& report){
        if (!std::isfinite(report.value_at_risk_backtest.exception_rate) ||
            !std::isfinite(report.maximum_drawdown) ||
            !std::isfinite(report.annualized_volatility)){
            throw std::invalid_argument("backtest report values must be finite");
        }
        std::ostringstream output;
        output<<std::setprecision(17);
        output<<"observations,exceptions,exception_rate,maximum_drawdown,annualized_volatility\n";
        output<<report.value_at_risk_backtest.observation_count<<",";
        output<<report.value_at_risk_backtest.exception_count<<",";
        output<<report.value_at_risk_backtest.exception_rate<<",";
        output<<report.maximum_drawdown<<",";
        output<<report.annualized_volatility<<"\n";
        return output.str();
    }
}