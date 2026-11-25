# C++ API
## Public include
Consumers can include the complete public API through:
```cpp
#include <riskforge/riskforge.hpp>
```
The umbrella header includes the public interfaces for random generation,
simulation, risk, portfolios, options, and backtesting.
## Version
```cpp
#include <riskforge/version.hpp>
const char* current_version=riskforge::version();
```
## API areas
### Random
```text
riskforge/random/
```
Includes Philox4x32-10, open-interval uniforms, normal quantiles, and Student-t
sampling.
### Simulation
```text
riskforge/simulation/
```
Includes GBM, Monte Carlo, parallel Monte Carlo, Student-t GBM, stochastic
volatility, parallel stochastic volatility, and jump diffusion.
### Risk
```text
riskforge/risk/
```
Includes Value at Risk, Expected Shortfall, tail aggregation, Monte Carlo risk,
parallel risk, and order-statistic confidence intervals.
### Portfolio
```text
riskforge/portfolio/
```
Includes correlation handling, Cholesky-based multi-asset simulation, portfolio
valuation, portfolio risk, and parallel portfolio risk.
### Options
```text
riskforge/options/
```
Includes Black-Scholes call and put pricing, Greeks, implied volatility,
volatility surfaces, Monte Carlo options, and Monte Carlo Greeks.
### Backtesting
```text
riskforge/backtesting/
```
Includes historical returns, historical risk, rolling risk, volatility,
drawdown, Sharpe ratio, VaR backtesting, unconditional and conditional
coverage, stress scenarios, calibration, reports, and risk comparisons.
## Error handling
Invalid numerical inputs are rejected with standard C++ exceptions. Callers
should validate or handle exceptions around public simulation and risk APIs.
## Reproducibility
Seeded simulation APIs are deterministic. Results should not depend on thread
scheduling or worker count when using APIs that guarantee deterministic
reduction.