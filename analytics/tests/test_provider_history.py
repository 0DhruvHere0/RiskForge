import numpy as np
from riskforge.data.instruments import Instrument
from riskforge.data.mock_provider import InMemoryInstrumentProvider
from riskforge.data.models import HistoricalPriceSeries
def test_provider_returns_historical_prices():
    instrument=Instrument(
        "TEST",
        "Test Stock",
        "stock",
        "NSE",
        "INR"
    )
    history=HistoricalPriceSeries(
        symbol="TEST",
        dates=[
            "2025-01-01",
            "2025-01-02",
        ],
        closes=np.array([
            100.0,
            105.0,
        ])
    )
    provider=InMemoryInstrumentProvider(
        [instrument],
        {"TEST": history}
    )
    result=provider.history(instrument)
    assert result.symbol=="TEST"
    np.testing.assert_array_equal(
        result.closes,
        np.array([100.0, 105.0])
    )
def test_provider_filters_instrument_type():
    provider=InMemoryInstrumentProvider([
        Instrument(
            "ABC",
            "ABC Stock",
            "stock",
            "NSE",
            "INR"
        ),
        Instrument(
            "ABC001",
            "ABC Mutual Fund",
            "mutual_fund",
            "AMFI",
            "INR"
        ),
    ])
    results=provider.search("abc", "mutual_fund")
    assert len(results)==1
    assert results[0].instrument_type=="mutual_fund"