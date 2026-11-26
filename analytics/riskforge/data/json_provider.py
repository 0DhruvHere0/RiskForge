import numpy as np
from .instruments import Instrument
from .models import HistoricalPriceSeries
class JsonMarketDataProvider:
    def __init__(
        self,
        client,
        search_endpoint: str,
        history_endpoint: str
    ):
        self._client=client
        self._search_endpoint=search_endpoint
        self._history_endpoint=history_endpoint
    def search(
        self,
        query: str,
        instrument_type: str|None=None
    ) -> list[Instrument]:
        payload=self._client.get_json(
            self._search_endpoint,
            {
                "query": query,
            }
        )
        instruments=[
            Instrument(
                item["symbol"],
                item["name"],
                item["instrument_type"],
                item["exchange"],
                item["currency"]
            )
            for item in payload["instruments"]
        ]
        if instrument_type is None:
            return instruments
        return [
            instrument
            for instrument in instruments
            if instrument.instrument_type==instrument_type
        ]
    def history(
        self,
        instrument: Instrument,
        start=None,
        end=None
    ) -> HistoricalPriceSeries:
        params={
            "symbol": instrument.symbol,
        }
        if start is not None:
            params["start"]=start.isoformat()
        if end is not None:
            params["end"]=end.isoformat()
        payload=self._client.get_json(
            self._history_endpoint,
            params
        )
        dates=payload["dates"]
        closes=np.asarray(payload["closes"],dtype=float)
        if len(dates)!=len(closes):
            raise ValueError(
                "dates and closes must have equal lengths"
            )
        return HistoricalPriceSeries(
            instrument.symbol,
            dates,
            closes
        )