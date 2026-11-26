from typing import Protocol
from .instruments import Instrument
class InstrumentProvider(Protocol):
    def search(
        self,
        query: str,
        instrument_type: str|None=None
    ) -> list[Instrument]:
        ...