import os
from datetime import date
from .market_data_factory import MarketDataFactoryConfig
from .market_data_factory import create_market_data_provider
from .provider import InstrumentProvider
class ConfiguredMarketDataProvider:
    def __init__(
        self,
        source: str|None=None,
        timeout: float|None=None
    ):
        selected_source=source or os.getenv(
            "RISKFORGE_MARKET_DATA_SOURCE",
            "alpha_vantage"
        )
        request_timeout=timeout or float(
            os.getenv(
                "RISKFORGE_MARKET_DATA_TIMEOUT",
                "10.0"
            )
        )
        config=MarketDataFactoryConfig(
            alphavantage_api_key=os.getenv(
                "ALPHAVANTAGE_API_KEY"
            ),
            request_timeout=request_timeout
        )
        self._provider=create_market_data_provider(
            selected_source,
            config
        )
    def search(self, query: str):
        return self._provider.search(query)
    def history(self, symbol, start: date, end: date):
        return self._provider.history(
            symbol,
            start,
            end
        )