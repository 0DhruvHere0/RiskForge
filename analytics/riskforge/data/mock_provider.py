from datetime import date
from .instruments import Instrument
from .models import HistoricalPriceSeries
class InMemoryInstrumentProvider:
    def __init__(
        self,
        instruments: list[Instrument],
        histories: dict[str, HistoricalPriceSeries]|None=None
    ):
        self._instruments=instruments
        self._histories=histories or {}
    def search(
        self,
        query: str,
        instrument_type: str|None=None
    ) -> list[Instrument]:
        normalized_query=query.strip().lower()
        return [
            instrument
            for instrument in self._instruments
            if (
                not instrument_type
                or instrument.instrument_type==instrument_type
            )
            and (
                normalized_query in instrument.symbol.lower()
                or normalized_query in instrument.name.lower()
            )
        ]
    def history(
        self,
        instrument: Instrument,
        start: date|None=None,
        end: date|None=None
    ) -> HistoricalPriceSeries:
        if instrument.symbol not in self._histories:
            raise KeyError(
                f"no historical data for {instrument.symbol}"
            )
        return self._histories[instrument.symbol]