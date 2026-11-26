import csv
import io
from datetime import date
from datetime import datetime
from datetime import timedelta
from urllib.parse import urlencode
import numpy as np
from .http_client import UrllibTextClient
from .instruments import Instrument
from .models import HistoricalPriceSeries
class AmfiProvider:
    def __init__(
        self,
        client=None,
        latest_endpoint: str="https://www.amfiindia.com/spages/NAVAll.txt",
        history_endpoint: str="https://portal.amfiindia.com/DownloadNAVHistoryReport_Po.aspx"
    ):
        self._client=client or UrllibTextClient()
        self._latest_endpoint=latest_endpoint
        self._history_endpoint=history_endpoint
    def search(
        self,
        query: str,
        instrument_type: str|None=None
    ) -> list[Instrument]:
        if instrument_type and instrument_type!="mutual_fund":
            return []
        normalized_query=query.strip().lower()
        instruments=[]
        for row in self._rows(self._latest_endpoint):
            if len(row)<6:
                continue
            symbol=row[0].strip()
            name=row[3].strip()
            if (
                normalized_query in symbol.lower()
                or normalized_query in name.lower()
            ):
                instruments.append(
                    Instrument(
                        symbol,
                        name,
                        "mutual_fund",
                        "AMFI",
                        "INR"
                    )
                )
        return instruments
    def latest_nav(self, scheme_code: str) -> float:
        for row in self._rows(self._latest_endpoint):
            if len(row)<6 or row[0].strip()!=scheme_code:
                continue
            return float(row[4].strip())
        raise KeyError(f"scheme not found: {scheme_code}")
    def history(
        self,
        instrument: Instrument,
        start: date|None=None,
        end: date|None=None
    ) -> HistoricalPriceSeries:
        if start is None or end is None:
            raise ValueError(
                "start and end dates are required for AMFI history"
            )
        if start>end:
            raise ValueError("start must not be after end")
        values={}
        current=start
        while current<=end:
            window_end=min(
                current+timedelta(days=89),
                end
            )
            query=urlencode({
                "mf": instrument.symbol,
                "frmdt": current.strftime("%d-%b-%Y"),
                "todt": window_end.strftime("%d-%b-%Y"),
            })
            payload=f"{self._history_endpoint}?{query}"
            for row in self._rows(payload):
                if len(row)<2:
                    continue
                parsed_date=self._parse_date(row[0].strip())
                if parsed_date is None:
                    continue
                values[parsed_date.isoformat()]=float(
                    row[1].strip()
                )
            current=window_end+timedelta(days=1)
        if not values:
            raise ValueError("no AMFI historical NAV values found")
        ordered_dates=sorted(values)
        return HistoricalPriceSeries(
            instrument.symbol,
            ordered_dates,
            np.asarray(
                [values[item] for item in ordered_dates],
                dtype=float
            )
        )
    def _rows(self, endpoint: str):
        text=self._client.get_text(endpoint)
        return csv.reader(
            io.StringIO(text),
            delimiter=";"
        )
    @staticmethod
    def _parse_date(value: str):
        for date_format in (
            "%d-%b-%Y",
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