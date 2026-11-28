from datetime import date
from .provider import InstrumentProvider
class CombinedMarketDataProvider:
    def __init__(
        self,
        stock_provider: InstrumentProvider,
        mutual_fund_provider: InstrumentProvider
    ):
        self._stock_provider=stock_provider
        self._mutual_fund_provider=mutual_fund_provider
        self._sources={}
    def search(self, query: str):
        stocks=self._stock_provider.search(query)
        mutual_funds=self._mutual_fund_provider.search(query)
        instruments=[]
        for instrument in stocks:
            self._sources[instrument.symbol]=(
                self._stock_provider,
                "alpha_vantage"
            )
            instruments.append(instrument)
        for instrument in mutual_funds:
            self._sources[instrument.symbol]=(
                self._mutual_fund_provider,
                "amfi"
            )
            instruments.append(instrument)
        return instruments
    def source_for(self, symbol: str):
        source=self._sources.get(symbol)
        if source is None:
            return "unknown"
        return source[1]
    def history(
        self,
        symbol: str,
        start: date,
        end: date
    ):
        provider=self._sources.get(
            symbol,
            (self._stock_provider, "alpha_vantage")
        )[0]
        return provider.history(
            symbol,
            start,
            end
        )