#include "riskforge/options/black_scholes.hpp"
#include "riskforge/options/black_scholes_put.hpp"
#include "riskforge/options/greeks.hpp"
#include "riskforge/options/implied_volatility.hpp"
#include "riskforge/options/put_greeks.hpp"
#include "riskforge/options/volatility_surface.hpp"
#include "riskforge/portfolio/multi_asset_gbm.hpp"
#include "riskforge/portfolio/portfolio.hpp"
#include "riskforge/portfolio/portfolio_risk.hpp"
#include "riskforge/risk/expected_shortfall.hpp"
#include "riskforge/risk/monte_carlo_risk.hpp"
#include "riskforge/risk/var.hpp"
#include "riskforge/simulation/gbm.hpp"
#include "riskforge/simulation/monte_carlo.hpp"
#include "riskforge/version.hpp"
#include "riskforge/backtesting/backtest_report.hpp"
#include "riskforge/backtesting/historical_returns.hpp"
#include "riskforge/backtesting/historical_risk.hpp"
#include "riskforge/backtesting/performance_metrics.hpp"
#include "riskforge/backtesting/var_backtest.hpp"
#include "riskforge/simulation/jump_diffusion.hpp"
#include "riskforge/simulation/parallel_stochastic_volatility.hpp"
#include "riskforge/simulation/stochastic_volatility.hpp"
#include "riskforge/simulation/student_t_gbm.hpp"
#include "riskforge/options/monte_carlo_greeks.hpp"
#include "riskforge/options/monte_carlo_options.hpp"
#include <span>
#include <cstddef>
#include <cstdint>
#include <pybind11/numpy.h>
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <vector>
namespace py=pybind11;
PYBIND11_MODULE(_native, module){
    module.doc()="Python bindings for the RiskForge C++ engine";
    py::class_<riskforge::options::BlackScholesInput> black_scholes_input(
        module,
        "BlackScholesInput"
    );
    black_scholes_input.def(py::init<>());
    black_scholes_input.def_readwrite(
        "spot",
        &riskforge::options::BlackScholesInput::spot
    );
    black_scholes_input.def_readwrite(
        "strike",
        &riskforge::options::BlackScholesInput::strike
    );
    black_scholes_input.def_readwrite(
        "risk_free_rate",
        &riskforge::options::BlackScholesInput::risk_free_rate
    );
    black_scholes_input.def_readwrite(
        "volatility",
        &riskforge::options::BlackScholesInput::volatility
    );
    black_scholes_input.def_readwrite(
        "time",
        &riskforge::options::BlackScholesInput::time
    );
    module.def("version", &riskforge::version);
    module.def(
        "gbm_terminal_price",
        &riskforge::simulation::gbm_terminal_price,
        py::arg("initial_price"),
        py::arg("drift"),
        py::arg("volatility"),
        py::arg("time"),
        py::arg("standard_normal")
    );
    module.def(
        "simulate_gbm_terminal_prices",
        [](
            double initial_price,
            double drift,
            double volatility,
            double time,
            std::size_t path_count,
            std::uint32_t seed
        ){
            const riskforge::simulation::GbmSimulationConfig config{
                initial_price,
                drift,
                volatility,
                time,
                path_count,
                seed
            };
            const auto prices=
                riskforge::simulation::simulate_gbm_terminal_prices(
                    config
                );
            py::array_t<double> result(prices.size());
            auto output=result.mutable_unchecked<1>();
            for (std::size_t index=0; index<prices.size(); ++index){
                output(index)=prices[index];
            }
            return result;
        },
        py::arg("initial_price"),
        py::arg("drift"),
        py::arg("volatility"),
        py::arg("time"),
        py::arg("path_count"),
        py::arg("seed")
    );
    module.def(
        "lognormal_value_at_risk",
        &riskforge::risk::lognormal_value_at_risk,
        py::arg("initial_price"),
        py::arg("drift"),
        py::arg("volatility"),
        py::arg("time"),
        py::arg("confidence_level")
    );
    module.def(
        "lognormal_expected_shortfall",
        &riskforge::risk::lognormal_expected_shortfall,
        py::arg("initial_price"),
        py::arg("drift"),
        py::arg("volatility"),
        py::arg("time"),
        py::arg("confidence_level")
    );
    module.def(
        "estimate_gbm_risk",
        [](
            double initial_price,
            double drift,
            double volatility,
            double time,
            std::size_t path_count,
            std::uint32_t seed,
            double confidence_level
        ){
            const riskforge::simulation::GbmSimulationConfig config{
                initial_price,
                drift,
                volatility,
                time,
                path_count,
                seed
            };
            const auto risk=
                riskforge::risk::estimate_gbm_risk(
                    config,
                    confidence_level
                );
            py::dict result;
            result["value_at_risk"]=risk.value_at_risk;
            result["expected_shortfall"]=risk.expected_shortfall;
            return result;
        },
        py::arg("initial_price"),
        py::arg("drift"),
        py::arg("volatility"),
        py::arg("time"),
        py::arg("path_count"),
        py::arg("seed"),
        py::arg("confidence_level")
    );
    module.def(
        "simulate_multi_asset_gbm_terminal_prices",
        [](
            const std::vector<double>& initial_prices,
            const std::vector<double>& drifts,
            const std::vector<double>& volatilities,
            const riskforge::portfolio::Matrix& correlation,
            double time,
            std::size_t path_count,
            std::uint32_t seed
        ){
            const riskforge::portfolio::MultiAssetGbmConfig config{
                initial_prices,
                drifts,
                volatilities,
                correlation,
                time,
                path_count,
                seed
            };
            const auto prices=
                riskforge::portfolio::
                simulate_multi_asset_gbm_terminal_prices(
                    config
                );
            const std::size_t asset_count=initial_prices.size();
            py::array_t<double> result({
                static_cast<py::ssize_t>(prices.size()),
                static_cast<py::ssize_t>(asset_count)
            });
            auto output=result.mutable_unchecked<2>();
            for (std::size_t path=0; path<prices.size(); ++path){
                for (std::size_t asset=0; asset<asset_count; ++asset){
                    output(path, asset)=prices[path][asset];
                }
            }
            return result;
        },
        py::arg("initial_prices"),
        py::arg("drifts"),
        py::arg("volatilities"),
        py::arg("correlation"),
        py::arg("time"),
        py::arg("path_count"),
        py::arg("seed")
    );
    module.def(
        "calculate_portfolio_losses",
        [](
            const std::vector<std::vector<double>>& terminal_prices,
            const std::vector<double>& initial_prices,
            const std::vector<double>& weights
        ){
            const auto losses=
                riskforge::portfolio::calculate_portfolio_losses(
                    terminal_prices,
                    initial_prices,
                    weights
                );
            py::array_t<double> result(losses.size());
            auto output=result.mutable_unchecked<1>();
            for (std::size_t index=0; index<losses.size(); ++index){
                output(index)=losses[index];
            }
            return result;
        },
        py::arg("terminal_prices"),
        py::arg("initial_prices"),
        py::arg("weights")
    );
    module.def(
        "estimate_portfolio_risk",
        [](
            const std::vector<std::vector<double>>& terminal_prices,
            const std::vector<double>& initial_prices,
            const std::vector<double>& weights,
            double confidence_level
        ){
            const auto risk=
                riskforge::portfolio::estimate_portfolio_risk(
                    terminal_prices,
                    initial_prices,
                    weights,
                    confidence_level
                );
            py::dict result;
            result["value_at_risk"]=risk.value_at_risk;
            result["expected_shortfall"]=risk.expected_shortfall;
            return result;
        },
        py::arg("terminal_prices"),
        py::arg("initial_prices"),
        py::arg("weights"),
        py::arg("confidence_level")
    );
    module.def(
        "black_scholes_call_price",
        &riskforge::options::black_scholes_call_price
    );
    module.def(
        "black_scholes_put_price",
        &riskforge::options::black_scholes_put_price
    );
    module.def(
        "black_scholes_call_delta",
        &riskforge::options::black_scholes_call_delta
    );
    module.def(
        "black_scholes_put_delta",
        &riskforge::options::black_scholes_put_delta
    );
    module.def(
        "black_scholes_call_gamma",
        &riskforge::options::black_scholes_call_gamma
    );
    module.def(
        "black_scholes_call_vega",
        &riskforge::options::black_scholes_call_vega
    );
    module.def(
        "black_scholes_call_theta",
        &riskforge::options::black_scholes_call_theta
    );
    module.def(
        "black_scholes_call_rho",
        &riskforge::options::black_scholes_call_rho
    );
    module.def(
        "black_scholes_put_gamma",
        &riskforge::options::black_scholes_put_gamma
    );
    module.def(
        "black_scholes_put_vega",
        &riskforge::options::black_scholes_put_vega
    );
    module.def(
        "black_scholes_put_theta",
        &riskforge::options::black_scholes_put_theta
    );
    module.def(
        "black_scholes_put_rho",
        &riskforge::options::black_scholes_put_rho
    );
    module.def(
        "black_scholes_implied_volatility",
        &riskforge::options::black_scholes_implied_volatility
    );
    module.def(
        "build_call_volatility_surface",
        &riskforge::options::build_call_volatility_surface
    );
    module.def(
        "historical_log_returns",
        [](
            const std::vector<double>& prices
        ){
            const auto returns=
                riskforge::backtesting::historical_log_returns(
                    std::span<const double>(
                        prices.data(),
                        prices.size()
                    )
                );
            py::array_t<double> result(returns.size());
            auto output=result.mutable_unchecked<1>();
            for (std::size_t index=0; index<returns.size(); ++index){
                output(index)=returns[index];
            }
            return result;
        },
        py::arg("prices")
    );
    module.def(
        "estimate_historical_risk",
        [](
            const std::vector<double>& log_returns,
            double confidence_level
        ){
            const auto risk=
                riskforge::backtesting::estimate_historical_risk(
                    std::span<const double>(
                        log_returns.data(),
                        log_returns.size()
                    ),
                    confidence_level
                );
            py::dict result;
            result["value_at_risk"]=risk.value_at_risk;
            result["expected_shortfall"]=risk.expected_shortfall;
            return result;
        },
        py::arg("log_returns"),
        py::arg("confidence_level")
    );
    module.def(
        "backtest_value_at_risk",
        [](
            const std::vector<double>& log_returns,
            double value_at_risk
        ){
            const auto backtest=
                riskforge::backtesting::backtest_value_at_risk(
                    std::span<const double>(
                        log_returns.data(),
                        log_returns.size()
                    ),
                    value_at_risk
                );
            py::dict result;
            result["observation_count"]=backtest.observation_count;
            result["exception_count"]=backtest.exception_count;
            result["exception_rate"]=backtest.exception_rate;
            return result;
        },
        py::arg("log_returns"),
        py::arg("value_at_risk")
    );
    module.def(
        "calculate_performance_metrics",
        [](
            const std::vector<double>& log_returns,
            double periods_per_year
        ){
            const auto metrics=
                riskforge::backtesting::calculate_performance_metrics(
                    std::span<const double>(
                        log_returns.data(),
                        log_returns.size()
                    ),
                    periods_per_year
                );
            py::dict result;
            result["total_log_return"]=metrics.total_log_return;
            result["total_compounded_return"]=
                metrics.total_compounded_return;
            result["annualized_return"]=metrics.annualized_return;
            return result;
        },
        py::arg("log_returns"),
        py::arg("periods_per_year")
    );
    module.def(
        "create_backtest_report",
        [](
            const std::vector<double>& log_returns,
            double value_at_risk,
            double periods_per_year
        ){
            const auto report=
                riskforge::backtesting::create_backtest_report(
                    std::span<const double>(
                        log_returns.data(),
                        log_returns.size()
                    ),
                    value_at_risk,
                    periods_per_year
                );
            py::dict result;
            result["observation_count"]=
                report.value_at_risk_backtest.observation_count;
            result["exception_count"]=
                report.value_at_risk_backtest.exception_count;
            result["exception_rate"]=
                report.value_at_risk_backtest.exception_rate;
            result["maximum_drawdown"]=report.maximum_drawdown;
            result["annualized_volatility"]=
                report.annualized_volatility;
            return result;
        },
        py::arg("log_returns"),
        py::arg("value_at_risk"),
        py::arg("periods_per_year")
    );
    module.def(
        "student_t_gbm_terminal_price",
        &riskforge::simulation::student_t_gbm_terminal_price,
        py::arg("initial_price"),
        py::arg("drift"),
        py::arg("volatility"),
        py::arg("time"),
        py::arg("degrees_of_freedom"),
        py::arg("seed"),
        py::arg("sample")
    );
    module.def(
        "stochastic_volatility_terminal_price",
        &riskforge::simulation::stochastic_volatility_terminal_price,
        py::arg("initial_price"),
        py::arg("drift"),
        py::arg("initial_variance"),
        py::arg("long_term_variance"),
        py::arg("mean_reversion"),
        py::arg("volatility_of_variance"),
        py::arg("time"),
        py::arg("steps"),
        py::arg("seed"),
        py::arg("sample")
    );
    module.def(
        "parallel_stochastic_volatility_terminal_prices",
        [](
            double initial_price,
            double drift,
            double initial_variance,
            double long_term_variance,
            double mean_reversion,
            double volatility_of_variance,
            double time,
            std::size_t steps,
            std::size_t path_count,
            std::size_t worker_count,
            std::uint32_t seed
        ){
            const auto prices=
                riskforge::simulation::
                parallel_stochastic_volatility_terminal_prices(
                    initial_price,
                    drift,
                    initial_variance,
                    long_term_variance,
                    mean_reversion,
                    volatility_of_variance,
                    time,
                    steps,
                    path_count,
                    worker_count,
                    seed
                );
            py::array_t<double> result(prices.size());
            auto output=result.mutable_unchecked<1>();
            for (std::size_t index=0; index<prices.size(); ++index){
                output(index)=prices[index];
            }
            return result;
        },
        py::arg("initial_price"),
        py::arg("drift"),
        py::arg("initial_variance"),
        py::arg("long_term_variance"),
        py::arg("mean_reversion"),
        py::arg("volatility_of_variance"),
        py::arg("time"),
        py::arg("steps"),
        py::arg("path_count"),
        py::arg("worker_count"),
        py::arg("seed")
    );
    module.def(
        "jump_diffusion_terminal_price",
        &riskforge::simulation::jump_diffusion_terminal_price,
        py::arg("initial_price"),
        py::arg("drift"),
        py::arg("volatility"),
        py::arg("jump_intensity"),
        py::arg("jump_mean"),
        py::arg("jump_volatility"),
        py::arg("time"),
        py::arg("seed"),
        py::arg("sample")
    );
    module.def(
        "monte_carlo_european_call_price",
        [](
            double initial_price,
            double drift,
            double volatility,
            double time,
            std::size_t path_count,
            std::uint32_t seed,
            double strike,
            double risk_free_rate,
            std::size_t worker_count
        ){
            const riskforge::simulation::GbmSimulationConfig config{
                initial_price,
                drift,
                volatility,
                time,
                path_count,
                seed
            };
            return riskforge::options::monte_carlo_european_call_price(
                config,
                strike,
                risk_free_rate,
                worker_count
            );
        },
        py::arg("initial_price"),
        py::arg("drift"),
        py::arg("volatility"),
        py::arg("time"),
        py::arg("path_count"),
        py::arg("seed"),
        py::arg("strike"),
        py::arg("risk_free_rate"),
        py::arg("worker_count")
    );
    module.def(
        "monte_carlo_european_put_price",
        [](
            double initial_price,
            double drift,
            double volatility,
            double time,
            std::size_t path_count,
            std::uint32_t seed,
            double strike,
            double risk_free_rate,
            std::size_t worker_count
        ){
            const riskforge::simulation::GbmSimulationConfig config{
                initial_price,
                drift,
                volatility,
                time,
                path_count,
                seed
            };
            return riskforge::options::monte_carlo_european_put_price(
                config,
                strike,
                risk_free_rate,
                worker_count
            );
        },
        py::arg("initial_price"),
        py::arg("drift"),
        py::arg("volatility"),
        py::arg("time"),
        py::arg("path_count"),
        py::arg("seed"),
        py::arg("strike"),
        py::arg("risk_free_rate"),
        py::arg("worker_count")
    );
    module.def(
        "monte_carlo_call_delta",
        [](
            double initial_price,
            double drift,
            double volatility,
            double time,
            std::size_t path_count,
            std::uint32_t seed,
            double strike,
            double risk_free_rate,
            std::size_t worker_count,
            double spot_bump
        ){
            const riskforge::simulation::GbmSimulationConfig config{
                initial_price,
                drift,
                volatility,
                time,
                path_count,
                seed
            };
            return riskforge::options::monte_carlo_call_delta(
                config,
                strike,
                risk_free_rate,
                worker_count,
                spot_bump
            );
        },
        py::arg("initial_price"),
        py::arg("drift"),
        py::arg("volatility"),
        py::arg("time"),
        py::arg("path_count"),
        py::arg("seed"),
        py::arg("strike"),
        py::arg("risk_free_rate"),
        py::arg("worker_count"),
        py::arg("spot_bump")
    );
    module.def(
        "monte_carlo_call_gamma",
        [](
            double initial_price,
            double drift,
            double volatility,
            double time,
            std::size_t path_count,
            std::uint32_t seed,
            double strike,
            double risk_free_rate,
            std::size_t worker_count,
            double spot_bump
        ){
            const riskforge::simulation::GbmSimulationConfig config{
                initial_price,
                drift,
                volatility,
                time,
                path_count,
                seed
            };
            return riskforge::options::monte_carlo_call_gamma(
                config,
                strike,
                risk_free_rate,
                worker_count,
                spot_bump
            );
        },
        py::arg("initial_price"),
        py::arg("drift"),
        py::arg("volatility"),
        py::arg("time"),
        py::arg("path_count"),
        py::arg("seed"),
        py::arg("strike"),
        py::arg("risk_free_rate"),
        py::arg("worker_count"),
        py::arg("spot_bump")
    );
    module.def(
        "monte_carlo_call_vega",
        [](
            double initial_price,
            double drift,
            double volatility,
            double time,
            std::size_t path_count,
            std::uint32_t seed,
            double strike,
            double risk_free_rate,
            std::size_t worker_count,
            double volatility_bump
        ){
            const riskforge::simulation::GbmSimulationConfig config{
                initial_price,
                drift,
                volatility,
                time,
                path_count,
                seed
            };
            return riskforge::options::monte_carlo_call_vega(
                config,
                strike,
                risk_free_rate,
                worker_count,
                volatility_bump
            );
        },
        py::arg("initial_price"),
        py::arg("drift"),
        py::arg("volatility"),
        py::arg("time"),
        py::arg("path_count"),
        py::arg("seed"),
        py::arg("strike"),
        py::arg("risk_free_rate"),
        py::arg("worker_count"),
        py::arg("volatility_bump")
    );
}