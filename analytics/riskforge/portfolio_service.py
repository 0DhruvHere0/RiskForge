from dataclasses import dataclass
from datetime import date
from .data.portfolio_data import PortfolioDataService
from .data.portfolio_data import PortfolioHolding
from .data.portfolio_workflow import PortfolioDataset
from .data.portfolio_workflow import PortfolioWorkflow
from .portfolio_forecast import ForecastHolding
from .portfolio_forecast import PortfolioForecast
from .portfolio_forecast import PortfolioForecaster
from .portfolio_forecast_analysis import PortfolioForecastSummary
from .portfolio_forecast_analysis import summarize_portfolio_forecast
@dataclass(frozen=True)
class PortfolioAnalysisResult:
    dataset: PortfolioDataset
    forecast: PortfolioForecast
    summary: PortfolioForecastSummary
class PortfolioAnalysisService:
    def __init__(
        self,
        data_service: PortfolioDataService,
        forecaster: PortfolioForecaster
    ):
        self._workflow=PortfolioWorkflow(data_service)
        self._forecaster=forecaster
    def analyze(
        self,
        holdings: list[PortfolioHolding],
        forecast_holdings: list[ForecastHolding],
        quantities: dict[str, float],
        start: date,
        end: date,
        horizon: float,
        path_count: int,
        seed: int
    ) -> PortfolioAnalysisResult:
        dataset=self._workflow.load_dataset(
            holdings,
            start,
            end
        )
        forecast=self._forecaster.forecast(
            forecast_holdings,
            horizon,
            path_count,
            seed
        )
        summary=summarize_portfolio_forecast(
            forecast,
            forecast_holdings,
            quantities
        )
        return PortfolioAnalysisResult(
            dataset=dataset,
            forecast=forecast,
            summary=summary
        )