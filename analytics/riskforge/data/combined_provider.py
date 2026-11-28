from datetime import date
from .provider import InstrumentProvider
class CombinedMarketDataProvider:
    def __init__(
        self,
        stock_provider: InstrumentProvider,
        mutual_fund_provider: InstrumentProvider,
        mutual_fund_history_provider=None
    ):
        self._stock_provider=stock_provider
        self._mutual_fund_provider=mutual_fund_provider
        self._mutual_fund_history_provider=(
            mutual_fund_history_provider
            or mutual_fund_provider
        )
        self._sources={}
        self._instruments={}
    def search(self, query: str):
        stocks=self._stock_provider.search(query)
        mutual_funds=self._mutual_fund_provider.search(query)
        instruments=[]
        for instrument in stocks:
            self._sources[instrument.symbol]=(
                self._stock_provider,
                "alpha_vantage"
            )
            self._instruments[instrument.symbol]=instrument
            instruments.append(instrument)
        for instrument in mutual_funds:
            self._sources[instrument.symbol]=(
                self._mutual_fund_history_provider,
                "amfi"
            )
            self._instruments[instrument.symbol]=instrument
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
        source=self._sources.get(symbol)
        instrument=self._instruments.get(symbol)
        if source is None or instrument is None:
            matches=self.search(symbol)
            instrument=next(
                (
                    item
                    for item in matches
                    if item.symbol==symbol
                ),
                None
            )
            if instrument is None:
                raise ValueError(
                    f"instrument not found: {symbol}"
                )
            source=self._sources[symbol]
        return source[0].history(
            instrument,
            start,
            end
        )