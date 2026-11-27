def test_allowed_origins_reads_environment(monkeypatch):
    monkeypatch.setenv(
        "RISKFORGE_ALLOWED_ORIGINS",
        "http://localhost:3000,https://riskforge.example"
    )
    from riskforge.security import allowed_origins
    assert allowed_origins()==[
        "http://localhost:3000",
        "https://riskforge.example"
    ]
def test_allowed_origins_uses_local_default(monkeypatch):
    monkeypatch.delenv(
        "RISKFORGE_ALLOWED_ORIGINS",
        raising=False
    )
    from riskforge.security import allowed_origins
    assert allowed_origins()==[
        "http://localhost:3000"
    ]
def test_api_key_is_optional_in_development(monkeypatch):
    monkeypatch.delenv(
        "RISKFORGE_API_KEY",
        raising=False
    )
    from riskforge.security import require_api_key
    assert require_api_key(None) is None
def test_api_key_rejects_invalid_value(monkeypatch):
    monkeypatch.setenv(
        "RISKFORGE_API_KEY",
        "secret-key"
    )
    from fastapi import HTTPException
    from riskforge.security import require_api_key
    try:
        require_api_key("wrong-key")
        assert False
    except HTTPException as error:
        assert error.status_code==401