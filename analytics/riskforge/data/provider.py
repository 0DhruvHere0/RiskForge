from datetime import date
from typing import Protocol
from .instruments import Instrument
from .models import HistoricalPriceSeries
class InstrumentProvider(Protocol):
    def search(
        self,
        query: str,
        instrument_type: str|None=None
    ) -> list[Instrument]:
        ...
    def history(
        self,
        instrument: Instrument,
        start: date|None=None,
        end: date|None=None
    ) -> HistoricalPriceSeries:
        ...