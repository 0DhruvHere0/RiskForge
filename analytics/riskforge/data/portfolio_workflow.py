from dataclasses import dataclass
from datetime import date
import numpy as np
from .models import HistoricalPriceSeries
from .portfolio_data import PortfolioDataService
from .portfolio_data import PortfolioHolding
@dataclass(frozen=True)
class PortfolioDataset:
    holdings: tuple[PortfolioHolding, ...]
    dates: list[str]
    closing_prices: np.ndarray
    histories: dict[str, HistoricalPriceSeries]
class PortfolioWorkflow:
    def __init__(self, data_service: PortfolioDataService):
        self._data_service=data_service
    def load_dataset(
        self,
        holdings: list[PortfolioHolding],
        start: date,
        end: date
    ) -> PortfolioDataset:
        histories=self._data_service.load_history(
            holdings,
            start,
            end
        )
        dates, closing_prices=self._data_service.align_closing_prices(
            histories
        )
        return PortfolioDataset(
            holdings=tuple(holdings),
            dates=dates,
            closing_prices=closing_prices,
            histories=histories
        )