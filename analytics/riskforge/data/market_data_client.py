from typing import Protocol
class MarketDataClient(Protocol):
    def get_json(
        self,
        endpoint: str,
        params: dict[str, str]
    ) -> dict:
        ...