#include "riskforge/backtesting/backtest_report.hpp"
#include "riskforge/backtesting/drawdown.hpp"
#include "riskforge/backtesting/historical_volatility.hpp"
namespace riskforge::backtesting{
    BacktestReport create_backtest_report(
        std::span<const double> log_returns,
        double value_at_risk,
        double periods_per_year
    ){
        return BacktestReport{
            backtest_value_at_risk(log_returns, value_at_risk),
            maximum_drawdown(log_returns),
            annualized_historical_volatility(log_returns, periods_per_year)
        };
    }
}