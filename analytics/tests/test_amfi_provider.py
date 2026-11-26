from datetime import date
from riskforge.data import AmfiProvider
class FakeAmfiClient:
    def get_text(self, endpoint):
        if "DownloadNAVHistoryReport" in endpoint:
            return (
                "Date;Net Asset Value\n"
                "01-Jan-2025;100.00\n"
                "02-Jan-2025;101.50\n"
            )
        return (
            "Scheme Code;ISIN Div Payout/ISIN Growth;"
            "ISIN Div Reinvestment;Scheme Name;Net Asset Value;Date\n"
            "100001;INF000000001;INF000000002;"
            "Test Equity Fund;125.50;25-Nov-2026\n"
        )
def test_amfi_search():
    provider=AmfiProvider(FakeAmfiClient())
    results=provider.search("equity")
    assert len(results)==1
    assert results[0].symbol=="100001"
def test_amfi_latest_nav():
    provider=AmfiProvider(FakeAmfiClient())
    assert provider.latest_nav("100001")==125.50
def test_amfi_historical_nav():
    provider=AmfiProvider(FakeAmfiClient())
    instrument=provider.search("equity")[0]
    history=provider.history(
        instrument,
        date(2025, 1, 1),
        date(2025, 1, 2)
    )
    assert history.dates==[
        "2025-01-01",
        "2025-01-02",
    ]
    assert history.closes.tolist()==[
        100.0,
        101.5,
    ]