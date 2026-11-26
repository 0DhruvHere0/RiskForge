from dataclasses import dataclass
from .holdings import Holding
@dataclass(frozen=True)
class PortfolioRequest:
    holdings: list[Holding]
    holding_period_years: float
    confidence_level: float=0.95