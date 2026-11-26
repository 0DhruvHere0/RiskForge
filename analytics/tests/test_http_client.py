import json
from riskforge.data.http_client import UrllibJsonClient
class FakeResponse:
    def __init__(self, payload):
        self._payload=payload
    def __enter__(self):
        return self
    def __exit__(self, *args):
        return False
    def read(self):
        return json.dumps(self._payload).encode("utf-8")
def test_http_client_decodes_json(monkeypatch):
    def fake_urlopen(request, timeout):
        assert request.full_url=="https://example.test/search?q=test"
        assert timeout==5.0
        return FakeResponse({"ok": True})
    monkeypatch.setattr(
        "riskforge.data.http_client.urlopen",
        fake_urlopen
    )
    client=UrllibJsonClient(
        "https://example.test",
        timeout=5.0
    )
    assert client.get_json(
        "search",
        {"q": "test"}
    )=={"ok": True}