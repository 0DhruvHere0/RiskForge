from dataclasses import dataclass
import numpy as np
@dataclass(frozen=True)
class HistoricalPriceSeries:
    symbol: str
    dates: list[str]
    closes: np.ndarray