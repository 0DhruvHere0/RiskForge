import csv
import math
from pathlib import Path
import numpy as np
from .models import HistoricalPriceSeries
def load_price_history_csv(
    path: str|Path,
    symbol: str
):
    dates=[]
    closes=[]
    with Path(path).open(newline="", encoding="utf-8") as file:
        reader=csv.DictReader(file)
        if reader.fieldnames is None or "close" not in reader.fieldnames:
            raise ValueError("CSV must contain a close column")
        date_column="date" if "date" in reader.fieldnames else "timestamp"
        if date_column not in reader.fieldnames:
            raise ValueError("CSV must contain date or timestamp")
        for row in reader:
            close=float(row["close"])
            if not math.isfinite(close) or close<=0.0:
                raise ValueError("close values must be positive and finite")
            dates.append(row[date_column])
            closes.append(close)
    if len(closes)<2:
        raise ValueError("at least two price observations are required")
    return HistoricalPriceSeries(
        symbol=symbol,
        dates=dates,
        closes=np.asarray(closes,dtype=float)
    )