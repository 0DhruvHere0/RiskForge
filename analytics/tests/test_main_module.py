import riskforge.__main__ as main_module
def test_main_starts_uvicorn(monkeypatch):
    calls={}
    def fake_create_server():
        return "application"
    def fake_run(application, host, port):
        calls["application"]=application
        calls["host"]=host
        calls["port"]=port
    monkeypatch.setattr(
        main_module,
        "create_server",
        fake_create_server
    )
    monkeypatch.setattr(
        main_module.uvicorn,
        "run",
        fake_run
    )
    monkeypatch.setenv(
        "RISKFORGE_HOST",
        "0.0.0.0"
    )
    monkeypatch.setenv(
        "RISKFORGE_PORT",
        "9000"
    )
    main_module.main()
    assert calls=={
        "application": "application",
        "host": "0.0.0.0",
        "port": 9000
    }