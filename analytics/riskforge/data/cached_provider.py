from datetime import date
from .instruments import Instrument
from .models import HistoricalPriceSeries
class CachedInstrumentProvider:
    def __init__(self, provider):
        self._provider=provider
        self._search_cache={}
        self._history_cache={}
    def search(
        self,
        query: str,
        instrument_type: str|None=None
    ) -> list[Instrument]:
        key=(query.strip().lower(), instrument_type)
        if key not in self._search_cache:
            self._search_cache[key]=self._provider.search(
                query,
                instrument_type
            )
        return self._search_cache[key]
    def history(
        self,
        instrument: Instrument,
        start: date|None=None,
        end: date|None=None
    ) -> HistoricalPriceSeries:
        key=(instrument.symbol, start, end)
        if key not in self._history_cache:
            self._history_cache[key]=self._provider.history(
                instrument,
                start,
                end
            )
        return self._history_cache[key]