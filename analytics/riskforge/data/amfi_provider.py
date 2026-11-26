import csv
import io
from .http_client import UrllibTextClient
from .instruments import Instrument
class AmfiProvider:
    def __init__(
        self,
        client=None,
        endpoint: str="https://www.amfiindia.com/spages/NAVAll.txt"
    ):
        self._client=client or UrllibTextClient()
        self._endpoint=endpoint
    def search(
        self,
        query: str,
        instrument_type: str|None=None
    ) -> list[Instrument]:
        if instrument_type and instrument_type!="mutual_fund":
            return []
        normalized_query=query.strip().lower()
        instruments=[]
        for row in self._rows():
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
        for row in self._rows():
            if len(row)<6 or row[0].strip()!=scheme_code:
                continue
            return float(row[4].strip())
        raise KeyError(f"scheme not found: {scheme_code}")
    def _rows(self):
        text=self._client.get_text(self._endpoint)
        return csv.reader(
            io.StringIO(text),
            delimiter=";"
        )