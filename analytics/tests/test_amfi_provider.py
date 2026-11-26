from riskforge.data import AmfiProvider
class FakeAmfiClient:
    def get_text(self, endpoint):
        return (
            "Scheme Code;ISIN Div Payout/ISIN Growth;"
            "ISIN Div Reinvestment;Scheme Name;Net Asset Value;Date\n"
            "100001;INF000000001;INF000000002;"
            "Test Equity Fund;125.50;25-Nov-2026\n"
            "100002;INF000000003;INF000000004;"
            "Test Debt Fund;98.25;25-Nov-2026\n"
        )
def test_amfi_search():
    provider=AmfiProvider(FakeAmfiClient())
    results=provider.search("equity")
    assert len(results)==1
    assert results[0].symbol=="100001"
    assert results[0].instrument_type=="mutual_fund"
def test_amfi_latest_nav():
    provider=AmfiProvider(FakeAmfiClient())
    assert provider.latest_nav("100001")==125.50