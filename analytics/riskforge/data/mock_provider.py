from .instruments import Instrument
class InMemoryInstrumentProvider:
    def __init__(self, instruments: list[Instrument]):
        self._instruments=instruments
    def search(
        self,
        query: str,
        instrument_type: str|None=None
    ) -> list[Instrument]:
        normalized_query=query.strip().lower()
        return [
            instrument
            for instrument in self._instruments
            if normalized_query in instrument.symbol.lower()
            or normalized_query in instrument.name.lower()
        ]