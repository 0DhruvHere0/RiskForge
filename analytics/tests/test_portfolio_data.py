from datetime import date
import numpy as np
import pytest
from riskforge.data.instruments import Instrument
from riskforge.data.models import HistoricalPriceSeries
from riskforge.data.portfolio_data import PortfolioDataService
from riskforge.data.portfolio_data import PortfolioHolding
class FakeProvider:
    def __init__(self):
        self._histories={
            "AAA": HistoricalPriceSeries(
                symbol="AAA",
                dates=["2025-01-01", "2025-01-02", "2025-01-03"],
                closes=np.asarray([100.0, 101.0, 102.0])
            ),
            "BBB": HistoricalPriceSeries(
                symbol="BBB",
                dates=["2025-01-02", "2025-01-03", "2025-01-04"],
                closes=np.asarray([200.0, 202.0, 204.0])
            )
        }
    def search(self, query: str):
        return [
            Instrument(
                symbol="AAA",
                name="Alpha Asset",
                instrument_type="stock",
                exchange="TEST",
                currency="USD"
            )
        ]
    def history(
        self,
        symbol: str,
        start: date,
        end: date
    ):
        return self._histories[symbol]
def test_search_delegates_to_provider():
    service=PortfolioDataService(FakeProvider())
    result=service.search("alpha")
    assert result[0].symbol=="AAA"
def test_load_history_for_holdings():
    service=PortfolioDataService(FakeProvider())
    holdings=[
        PortfolioHolding(
            symbol="AAA",
            quantity=2.0,
            purchase_price=95.0
        )
    ]
    result=service.load_history(
        holdings,
        date(2025, 1, 1),
        date(2025, 1, 3)
    )
    assert list(result)==["AAA"]
    assert result["AAA"].closes.tolist()==[100.0, 101.0, 102.0]
def test_align_closing_prices_uses_common_dates():
    provider=FakeProvider()
    service=PortfolioDataService(provider)
    dates, prices=service.align_closing_prices(
        {
            "AAA": provider._histories["AAA"],
            "BBB": provider._histories["BBB"]
        }
    )
    assert dates==["2025-01-02", "2025-01-03"]
    np.testing.assert_allclose(
        prices,
        np.asarray(
            [
                [101.0, 200.0],
                [102.0, 202.0]
            ]
        )
    )
def test_rejects_empty_holdings():
    service=PortfolioDataService(FakeProvider())
    with pytest.raises(ValueError):
        service.load_history(
            [],
            date(2025, 1, 1),
            date(2025, 1, 3)
        )
def test_rejects_invalid_holding_quantity():
    service=PortfolioDataService(FakeProvider())
    holdings=[
        PortfolioHolding(
            symbol="AAA",
            quantity=0.0,
            purchase_price=95.0
        )
    ]
    with pytest.raises(ValueError):
        service.load_history(
            holdings,
            date(2025, 1, 1),
            date(2025, 1, 3)
        )