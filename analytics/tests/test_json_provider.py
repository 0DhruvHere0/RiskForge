from datetime import date
from riskforge.data import Instrument
from riskforge.data import JsonMarketDataProvider
class FakeClient:
    def get_json(self, endpoint, params):
        if endpoint=="search":
            return {
                "instruments": [
                    {
                        "symbol": "TEST",
                        "name": "Test Stock",
                        "instrument_type": "stock",
                        "exchange": "NSE",
                        "currency": "INR",
                    },
                    {
                        "symbol": "FUND001",
                        "name": "Test Fund",
                        "instrument_type": "mutual_fund",
                        "exchange": "AMFI",
                        "currency": "INR",
                    },
                ]
            }
        return {
            "dates": [
                "2025-01-01",
                "2025-01-02",
            ],
            "closes": [
                100.0,
                105.0,
            ],
        }
def test_json_provider_search():
    provider=JsonMarketDataProvider(
        FakeClient(),
        "search",
        "history"
    )
    results=provider.search("test", "stock")
    assert len(results)==1
    assert results[0].symbol=="TEST"
def test_json_provider_history():
    instrument=Instrument(
        "TEST",
        "Test Stock",
        "stock",
        "NSE",
        "INR"
    )
    provider=JsonMarketDataProvider(
        FakeClient(),
        "search",
        "history"
    )
    history=provider.history(
        instrument,
        date(2025, 1, 1),
        date(2025, 1, 2)
    )
    assert history.symbol=="TEST"
    assert history.closes.tolist()==[100.0, 105.0]