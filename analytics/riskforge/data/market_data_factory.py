from dataclasses import dataclass
from .alpha_vantage_provider import AlphaVantageProvider
from .amfi_provider import AmfiProvider
from .combined_provider import CombinedMarketDataProvider
from .http_client import UrllibJsonClient
from .http_client import UrllibTextClient
from .mfapi_provider import MfapiProvider
from .provider import InstrumentProvider
@dataclass(frozen=True)
class MarketDataFactoryConfig:
    alphavantage_api_key: str|None=None
    request_timeout: float=10.0
def create_market_data_provider(
    source: str,
    config: MarketDataFactoryConfig
) -> InstrumentProvider:
    normalized_source=source.strip().lower()
    if normalized_source=="alpha_vantage":
        if not config.alphavantage_api_key:
            raise ValueError(
                "Alpha Vantage API key is required"
            )
        client=UrllibJsonClient(
            "https://www.alphavantage.co",
            timeout=config.request_timeout
        )
        return AlphaVantageProvider(
            api_key=config.alphavantage_api_key,
            client=client
        )
    if normalized_source=="amfi":
        client=UrllibTextClient(
            timeout=config.request_timeout
        )
        return AmfiProvider(
            client=client
        )
    if normalized_source=="combined":
        if not config.alphavantage_api_key:
            raise ValueError(
                "Alpha Vantage API key is required"
            )
        stock_client=UrllibJsonClient(
            "https://www.alphavantage.co",
            timeout=config.request_timeout
        )
        amfi_client=UrllibTextClient(
            timeout=config.request_timeout
        )
        mfapi_client=UrllibJsonClient(
            "https://api.mfapi.in",
            timeout=config.request_timeout
        )
        stock_provider=AlphaVantageProvider(
            api_key=config.alphavantage_api_key,
            client=stock_client
        )
        mutual_fund_provider=AmfiProvider(
            client=amfi_client
        )
        mutual_fund_history_provider=MfapiProvider(
            client=mfapi_client
        )
        return CombinedMarketDataProvider(
            stock_provider,
            mutual_fund_provider,
            mutual_fund_history_provider
        )
    raise ValueError(
        f"unsupported market data source: {source}"
    )