# RiskForge Decisions
## Phase 1
### Quantile confidence interval
The order-statistic confidence interval method is used for empirical
quantiles. It uses binomial-index bounds with a normal approximation.
### Coverage testing
The coverage test uses a fixed deterministic seed list and accepts a coverage
range instead of asserting one exact percentage.
The acceptance range for 200 seeds is 91%–99%.
### Offline coverage result
The deterministic 1000-seed offline coverage run produced:
- Covered seeds: 948
- Total seeds: 1000
- Observed coverage: 94.8%
The result is within the required 91%–99% acceptance range.
### Random number generation
Philox4x32-10 is used as the counter-based random number generator. Its output
is verified against Random123 known-answer values.
Uniform values are generated in the open interval `(0, 1)`.
Normal quantiles use the Wichura AS241 approximation and are tested against
reference values generated with SciPy.
### Sanitizer testing
AddressSanitizer and UndefinedBehaviorSanitizer are executed in GitHub Actions
using a Debug build.
---
## Phase 2
### Single-asset simulation
The initial single-asset model uses geometric Brownian motion:
```text
S(T) = S(0) × exp((μ - 0.5σ²)T + σ√T Z)
```
The implementation validates prices, volatility, time, and other numerical
inputs before simulation.
### Tail aggregation
Tail aggregation stores the largest losses required for Value at Risk and
Expected Shortfall calculations.
Invalid tail probabilities, incomplete input, non-finite values, and invalid
observation counts are rejected.
### Risk measures
Value at Risk and Expected Shortfall are calculated from the simulated loss
distribution.
Expected Shortfall is tested to be at least as large as Value at Risk for
positive-volatility cases.
### Deterministic reduction
Seeded simulations are deterministic. Repeating a simulation with the same
seed produces identical results.
Reduction tests verify that tail summaries are stable under repeated reduction
and supported input-order changes.
### Parallel simulation
Parallel simulation uses deterministic seed assignment and thread-safe
aggregation.
Parallel results are validated against serial simulation behavior.
---
## Phase 3
### Correlated multi-asset simulation
Multi-asset GBM uses a correlation matrix and a Cholesky factor to generate
correlated standard-normal shocks.
Correlation matrices are validated for compatible dimensions, symmetry, and
positive-definiteness.
### Portfolio construction
Portfolio values are calculated from asset prices and portfolio weights.
Input dimensions must match, and invalid or empty portfolios are rejected.
### Portfolio risk
Portfolio losses are calculated from initial and terminal portfolio values.
Portfolio Value at Risk and Expected Shortfall use the same validated risk
pipeline as single-asset simulations.
### Parallel portfolio simulation
Parallel portfolio simulation preserves deterministic seeded behavior while
distributing paths across workers.
Serial and parallel portfolio calculations are tested for consistency.
### Unified portfolio engine
The portfolio engine combines:
- Multi-asset GBM
- Correlated shocks
- Portfolio weights
- Monte Carlo paths
- Tail aggregation
- Value at Risk
- Expected Shortfall
---
## Phase 4
### Student-t simulation
Student-t random samples are standardized to unit variance before being used in
GBM.
The degrees of freedom must be greater than two so that the variance exists.
### Stochastic volatility
Stochastic-volatility simulation validates all model parameters and rejects
invalid time steps, volatility values, and non-finite inputs.
Seeded paths are deterministic.
### Jump diffusion
Jump-diffusion simulation supports jump intensity, jump size, and jump
volatility parameters.
Negative jump intensities and invalid parameters are rejected.
Zero jump intensity reduces to the corresponding diffusion behavior.
### Options pricing
Black-Scholes call and put prices are implemented with validation for spot,
strike, volatility, time, and interest-rate inputs.
The implementation includes:
- Call pricing
- Put pricing
- Delta
- Gamma
- Vega
- Theta
- Rho
- Implied volatility
- Volatility-surface support
### Monte Carlo options
Monte Carlo option pricing is tested against analytical Black-Scholes values
within an accepted numerical tolerance.
Seeded Monte Carlo option simulations are deterministic.
### Advanced-model testing
Advanced models include:
- Validation tests
- Determinism tests
- Analytical consistency tests
- Boundary tests
- Parallel consistency tests
- Release benchmarks
### Benchmark implementation
Google Benchmark is used for performance measurements.
Benchmark outputs use movable non-const values with:
```cpp
benchmark::DoNotOptimize(std::move(value));
benchmark::ClobberMemory();
```
This avoids deprecated const-reference usage.
### Platform benchmark warnings
macOS may report unavailable CPU-frequency information or failed thread
affinity.
These warnings affect benchmark metadata only and do not invalidate benchmark
results.
### Phase 4 verification
The complete debug suite passed with:
```text
181/181 tests passed
```
Advanced-model Release benchmarks completed successfully.
---
## General Engineering Decisions
### C++ standard
The C++ engine uses C++20.
### Testing framework
GoogleTest is used for unit, validation, deterministic, consistency, coverage,
and integration-style tests.
### Build system
CMake presets are used for Debug and Release builds.
### Continuous integration
GitHub Actions runs:
- Debug builds
- Unit tests
- Sanitizer builds
- CTest
- Coverage validation
### Reproducibility
All stochastic tests use explicit seeds. Randomness must not depend on thread
scheduling or execution order.
### Error handling
Invalid numerical inputs are rejected with standard C++ exceptions rather than
silently producing undefined or non-finite results.
### Scope control
Implementation discoveries that differ from the original design are recorded
in this document and do not automatically block development.