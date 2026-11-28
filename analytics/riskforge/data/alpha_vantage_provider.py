from datetime import date
import numpy as np
from .http_client import UrllibJsonClient
from .instruments import Instrument
from .models import HistoricalPriceSeries
class AlphaVantageProvider:
    def __init__(
        self,
        api_key: str,
        client=None
    ):
        if not api_key:
            raise ValueError("Alpha Vantage API key is required")
        self._api_key=api_key
        self._client=client or UrllibJsonClient(
            "https://www.alphavantage.co"
        )
    def search(
        self,
        query: str,
        instrument_type: str|None=None
    ) -> list[Instrument]:
        payload=self._client.get_json(
            "query",
            {
                "function": "SYMBOL_SEARCH",
                "keywords": query,
                "apikey": self._api_key
            }
        )
        self._check_response(payload)
        instruments=[]
        for item in payload.get(
            "bestMatches",
            []
        ):
            item_type=item.get(
                "3. type",
                "stock"
            ).lower()
            if instrument_type and item_type!=instrument_type:
                continue
            instruments.append(
                Instrument(
                    item["1. symbol"],
                    item["2. name"],
                    item_type,
                    item.get("4. region", ""),
                    item.get("8. currency", "")
                )
            )
        return instruments
    def history(
        self,
        instrument: Instrument,
        start: date|None=None,
        end: date|None=None
    ) -> HistoricalPriceSeries:
        payload=self._client.get_json(
            "query",
            {
                "function": "TIME_SERIES_DAILY",
                "symbol": instrument.symbol,
                "outputsize": "compact",
                "apikey": self._api_key
            }
        )
        self._check_response(payload)
        series=payload.get(
            "Time Series (Daily)"
        )
        if series is None:
            raise RuntimeError(
                "Alpha Vantage response did not contain daily prices"
            )
        rows=[]
        for date_text, values in series.items():
            current_date=date.fromisoformat(
                date_text
            )
            if start and current_date<start:
                continue
            if end and current_date>end:
                continue
            rows.append(
                (
                    date_text,
                    float(values["4. close"])
                )
            )
        rows.sort(
            key=lambda row: row[0]
        )
        if not rows:
            raise ValueError(
                "no historical prices found"
            )
        return HistoricalPriceSeries(
            instrument.symbol,
            [row[0] for row in rows],
            np.asarray(
                [row[1] for row in rows],
                dtype=float
            )
        )
    @staticmethod
    def _check_response(payload):
        if "Error Message" in payload:
            raise RuntimeError(
                payload["Error Message"]
            )
        if "Information" in payload:
            raise RuntimeError(
                payload["Information"]
            )
        if "Note" in payload:
            raise RuntimeError(
                payload["Note"]
            )