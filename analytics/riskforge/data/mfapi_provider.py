from datetime import date
from datetime import datetime
import numpy as np
from .http_client import UrllibJsonClient
from .instruments import Instrument
from .models import HistoricalPriceSeries
class MfapiProvider:
    def __init__(
        self,
        client=None,
        base_url: str="https://api.mfapi.in"
    ):
        self._client=client or UrllibJsonClient(
            base_url
        )
    def history(
        self,
        instrument: Instrument,
        start: date|None=None,
        end: date|None=None
    ) -> HistoricalPriceSeries:
        payload=self._client.get_json(
            f"mf/{instrument.symbol}",
            {}
        )
        rows=payload.get(
            "data",
            []
        )
        values=[]
        for row in rows:
            parsed_date=self._parse_date(
                row.get("date", "")
            )
            if parsed_date is None:
                continue
            if start and parsed_date<start:
                continue
            if end and parsed_date>end:
                continue
            values.append(
                (
                    parsed_date,
                    float(row["nav"])
                )
            )
        values.sort(
            key=lambda item: item[0]
        )
        if not values:
            raise ValueError(
                "no MFAPI historical NAV values found"
            )
        return HistoricalPriceSeries(
            instrument.symbol,
            [
                item[0].isoformat()
                for item in values
            ],
            np.asarray(
                [
                    item[1]
                    for item in values
                ],
                dtype=float
            )
        )
    @staticmethod
    def _parse_date(value: str):
        for date_format in (
            "%d-%m-%Y",
            "%d/%m/%Y",
            "%Y-%m-%d"
        ):
            try:
                return datetime.strptime(
                    value,
                    date_format
                ).date()
            except ValueError:
                continue
        return None