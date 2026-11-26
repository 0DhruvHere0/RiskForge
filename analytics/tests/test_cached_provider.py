from riskforge.data import CachedInstrumentProvider
from riskforge.data import InMemoryInstrumentProvider
from riskforge.data import Instrument
def test_cached_provider_reuses_search_result():
    instrument=Instrument(
        "TEST",
        "Test Stock",
        "stock",
        "NSE",
        "INR"
    )
    provider=InMemoryInstrumentProvider([instrument])
    cached=CachedInstrumentProvider(provider)
    first=cached.search("test")
    second=cached.search("test")
    assert first is second
    assert first[0].symbol=="TEST"
def test_cached_provider_reuses_history_result():
    from datetime import date
    import numpy as np
    from riskforge.data import HistoricalPriceSeries
    instrument=Instrument(
        "TEST",
        "Test Stock",
        "stock",
        "NSE",
        "INR"
    )
    history=HistoricalPriceSeries(
        "TEST",
        ["2025-01-01", "2025-01-02"],
        np.array([100.0, 105.0])
    )
    provider=InMemoryInstrumentProvider(
        [instrument],
        {"TEST": history}
    )
    cached=CachedInstrumentProvider(provider)
    first=cached.history(instrument)
    second=cached.history(instrument)
    assert first is second
    assert first.dates[0]=="2025-01-01"