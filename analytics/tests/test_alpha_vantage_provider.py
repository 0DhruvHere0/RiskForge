from datetime import date
from riskforge.data import AlphaVantageProvider
class FakeAlphaClient:
    def get_json(self, endpoint, params):
        if params["function"]=="SYMBOL_SEARCH":
            return {
                "bestMatches": [
                    {
                        "1. symbol": "TEST",
                        "2. name": "Test Stock",
                        "3. type": "Equity",
                        "4. region": "India",
                        "8. currency": "INR",
                    }
                ]
            }
        return {
            "Time Series (Daily)": {
                "2025-01-02": {
                    "4. close": "105.0"
                },
                "2025-01-01": {
                    "4. close": "100.0"
                }
            }
        }
def test_alpha_vantage_search():
    provider=AlphaVantageProvider(
        "test-key",
        FakeAlphaClient()
    )
    results=provider.search("test")
    assert len(results)==1
    assert results[0].symbol=="TEST"
    assert results[0].instrument_type=="equity"
def test_alpha_vantage_history():
    provider=AlphaVantageProvider(
        "test-key",
        FakeAlphaClient()
    )
    instrument=provider.search("test")[0]
    history=provider.history(
        instrument,
        date(2025, 1, 1),
        date(2025, 1, 2)
    )
    assert history.dates==[
        "2025-01-01",
        "2025-01-02",
    ]
    assert history.closes.tolist()==[100.0, 105.0]