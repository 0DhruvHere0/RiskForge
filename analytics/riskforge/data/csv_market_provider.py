import csv
from datetime import date
from pathlib import Path
from .csv_provider import load_price_history_csv
from .instruments import Instrument
from .models import HistoricalPriceSeries
class CsvMarketDataProvider:
    def __init__(
        self,
        catalog_path: str|Path,
        history_directory: str|Path
    ):
        self._catalog_path=Path(catalog_path)
        self._history_directory=Path(history_directory)
        self._instruments=self._load_catalog()
    def _load_catalog(self):
        instruments=[]
        with self._catalog_path.open(
            newline="",
            encoding="utf-8"
        ) as file:
            for row in csv.DictReader(file):
                instruments.append(
                    Instrument(
                        row["symbol"],
                        row["name"],
                        row["instrument_type"],
                        row["exchange"],
                        row["currency"]
                    )
                )
        return instruments
    def search(
        self,
        query: str,
        instrument_type: str|None=None
    ) -> list[Instrument]:
        normalized_query=query.strip().lower()
        return [
            instrument
            for instrument in self._instruments
            if (
                not instrument_type
                or instrument.instrument_type==instrument_type
            )
            and (
                normalized_query in instrument.symbol.lower()
                or normalized_query in instrument.name.lower()
            )
        ]
    def history(
        self,
        instrument: Instrument,
        start: date|None=None,
        end: date|None=None
    ) -> HistoricalPriceSeries:
        path=self._history_directory/f"{instrument.symbol}.csv"
        return load_price_history_csv(
            path,
            instrument.symbol
        )