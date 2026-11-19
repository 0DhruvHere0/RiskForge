# RiskForge Decisions
## Phase 1
### Quantile confidence interval
The order-statistic confidence interval method is used for empirical
quantiles. It uses binomial-index bounds with a normal approximation.
### Coverage testing
The CI coverage test uses a fixed deterministic seed list and accepts the
specified coverage range instead of asserting one exact percentage.
A larger 1000-seed offline coverage result will be recorded after the
coverage run is completed.
### Sanitizer testing
AddressSanitizer and UndefinedBehaviorSanitizer are executed in GitHub
Actions using a Debug build.
### Offline coverage result
The deterministic 1000-seed offline coverage run produced:
- Covered seeds: 948
- Total seeds: 1000
- Observed coverage: 94.8%
The result is within the required 91%–99% acceptance range.