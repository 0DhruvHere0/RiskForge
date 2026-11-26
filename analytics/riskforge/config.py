from dataclasses import dataclass
import os
from dotenv import load_dotenv
load_dotenv()
@dataclass(frozen=True)
class MarketDataConfig:
    alphavantage_api_key: str
    twelve_data_api_key: str
    alphavantage_base_url: str
    twelve_data_base_url: str
def load_market_data_config():
    return MarketDataConfig(
        os.getenv("ALPHAVANTAGE_API_KEY", ""),
        os.getenv("TWELVEDATA_API_KEY", ""),
        os.getenv(
            "ALPHAVANTAGE_BASE_URL",
            "https://www.alphavantage.co"
        ),
        os.getenv(
            "TWELVEDATA_BASE_URL",
            "https://api.twelvedata.com"
        )
    )