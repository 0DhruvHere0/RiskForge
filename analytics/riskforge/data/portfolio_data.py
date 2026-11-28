from dataclasses import dataclass
from datetime import date
from typing import Sequence
import numpy as np
from .models import HistoricalPriceSeries
from .provider import InstrumentProvider
@dataclass(frozen=True)
class PortfolioHolding:
    symbol: str
    quantity: float
    purchase_price: float
class PortfolioDataService:
    def __init__(self, provider: InstrumentProvider):
        self._provider=provider
    def search(self, query: str):
        return self._provider.search(query)
    def load_history(
        self,
        holdings: Sequence[PortfolioHolding],
        start: date,
        end: date
    ) -> dict[str, HistoricalPriceSeries]:
        if start>end:
            raise ValueError("start must not be after end")
        if not holdings:
            raise ValueError("holdings must not be empty")
        symbols={holding.symbol for holding in holdings}
        if len(symbols)!=len(holdings):
            raise ValueError("holding symbols must be unique")
        result={}
        for holding in holdings:
            if holding.quantity<=0.0:
                raise ValueError("holding quantity must be positive")
            if holding.purchase_price<=0.0:
                raise ValueError("purchase price must be positive")
            result[holding.symbol]=self._provider.history(
                holding.symbol,
                start,
                end
            )
        return result
    def align_closing_prices(
        self,
        histories: dict[str, HistoricalPriceSeries]
    ) -> tuple[list[str], np.ndarray]:
        if not histories:
            raise ValueError("histories must not be empty")
        common_dates=None
        for series in histories.values():
            dates=set(series.dates)
            common_dates=dates if common_dates is None else common_dates&dates
        dates=sorted(common_dates or [])
        if not dates:
            raise ValueError("histories have no common dates")
        columns=[]
        for series in histories.values():
            values=dict(zip(series.dates, series.closes))
            columns.append([values[item] for item in dates])
        return dates, np.asarray(columns, dtype=float).T
    def source_for(self, symbol: str):
        source_for=getattr(
            self._provider,
            "source_for",
            None
        )
        if source_for is None:
            return "configured_provider"
        return source_for(symbol)