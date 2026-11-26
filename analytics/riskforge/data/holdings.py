from dataclasses import dataclass
from datetime import date
from .instruments import Instrument
@dataclass(frozen=True)
class Holding:
    instrument: Instrument
    purchase_price: float
    quantity: float
    purchase_date: date