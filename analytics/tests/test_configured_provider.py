from datetime import date
from riskforge.data.configured_provider import ConfiguredMarketDataProvider
def test_configured_provider_uses_requested_source(monkeypatch):
    monkeypatch.setenv(
        "RISKFORGE_MARKET_DATA_SOURCE",
        "amfi"
    )
    provider=ConfiguredMarketDataProvider()
    assert provider._provider.__class__.__name__=="AmfiProvider"
def test_configured_provider_reads_timeout(monkeypatch):
    monkeypatch.setenv(
        "RISKFORGE_MARKET_DATA_SOURCE",
        "amfi"
    )
    monkeypatch.setenv(
        "RISKFORGE_MARKET_DATA_TIMEOUT",
        "5.0"
    )
    provider=ConfiguredMarketDataProvider()
    assert provider._provider is not None