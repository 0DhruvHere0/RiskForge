from datetime import date
import numpy as np
from riskforge.data import analyze_portfolio_holdings
from riskforge.data import HistoricalPriceSeries
from riskforge.data import Holding
from riskforge.data import InMemoryInstrumentProvider
from riskforge.data import Instrument
from riskforge.data import PortfolioRequest
def test_analyze_portfolio_holdings():
    instrument=Instrument(
        "TEST",
        "Test Stock",
        "stock",
        "NSE",
        "INR"
    )
    history=HistoricalPriceSeries(
        "TEST",
        [
            "2025-01-01",
            "2025-01-02",
            "2025-01-03",
        ],
        np.array([
            100.0,
            105.0,
            95.0
        ])
    )
    provider=InMemoryInstrumentProvider(
        [instrument],
        {"TEST": history}
    )
    request=PortfolioRequest(
        [
            Holding(
                instrument,
                100.0,
                10.0,
                date(2025, 1, 1)
            )
        ],
        10.0,
        0.95
    )
    results=analyze_portfolio_holdings(
        provider,
        request,
        date(2025, 1, 3)
    )
    assert len(results)==1
    assert results[0]["symbol"]=="TEST"
    assert np.isfinite(results[0]["value_at_risk"])
    assert np.isfinite(results[0]["expected_shortfall"])