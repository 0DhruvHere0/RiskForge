import json
from urllib.error import HTTPError
from urllib.error import URLError
from urllib.parse import urlencode
from urllib.request import Request
from urllib.request import urlopen
class UrllibJsonClient:
    def __init__(
        self,
        base_url: str,
        headers: dict[str, str]|None=None,
        timeout: float=10.0
    ):
        self._base_url=base_url.rstrip("/")
        self._headers=headers or {}
        self._timeout=timeout
    def get_json(
        self,
        endpoint: str,
        params: dict[str, str]
    ) -> dict:
        query=urlencode(params)
        url=f"{self._base_url}/{endpoint.lstrip('/')}"
        if query:
            url=f"{url}?{query}"
        request=Request(
            url,
            headers=self._headers,
            method="GET"
        )
        try:
            with urlopen(
                request,
                timeout=self._timeout
            ) as response:
                return json.loads(
                    response.read().decode("utf-8")
                )
        except (HTTPError, URLError, TimeoutError) as error:
            raise RuntimeError(
                "market-data request failed"
            ) from error