import pytest
from riskforge.data.market_data_factory import MarketDataFactoryConfig
from riskforge.data.market_data_factory import create_market_data_provider
from riskforge.data.alpha_vantage_provider import AlphaVantageProvider
from riskforge.data.amfi_provider import AmfiProvider
def test_creates_alpha_vantage_provider():
    provider=create_market_data_provider(
        "alpha_vantage",
        MarketDataFactoryConfig(
            alphavantage_api_key="test-key"
        )
    )
    assert isinstance(provider, AlphaVantageProvider)
def test_creates_amfi_provider():
    provider=create_market_data_provider(
        "amfi",
        MarketDataFactoryConfig()
    )
    assert isinstance(provider, AmfiProvider)
def test_rejects_alpha_vantage_without_api_key():
    with pytest.raises(ValueError):
        create_market_data_provider(
            "alpha_vantage",
            MarketDataFactoryConfig()
        )
def test_rejects_unknown_source():
    with pytest.raises(ValueError):
        create_market_data_provider(
            "unknown",
            MarketDataFactoryConfig()
        )