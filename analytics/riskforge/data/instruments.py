from dataclasses import dataclass
@dataclass(frozen=True)
class Instrument:
    symbol: str
    name: str
    instrument_type: str
    exchange: str
    currency: str