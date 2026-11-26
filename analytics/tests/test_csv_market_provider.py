from riskforge.data import CsvMarketDataProvider
def test_csv_market_data_provider(tmp_path):
    catalog=tmp_path/"catalog.csv"
    catalog.write_text(
        "symbol,name,instrument_type,exchange,currency\n"
        "TEST,Test Stock,stock,NSE,INR\n"
        "FUND001,Test Fund,mutual_fund,AMFI,INR\n"
    )
    history_directory=tmp_path/"history"
    history_directory.mkdir()
    (history_directory/"TEST.csv").write_text(
        "date,close\n"
        "2025-01-01,100.0\n"
        "2025-01-02,105.0\n"
    )
    provider=CsvMarketDataProvider(
        catalog,
        history_directory
    )
    results=provider.search("test")
    history=provider.history(results[0])
    assert len(results)==2
    assert history.symbol=="TEST"
    assert history.closes.tolist()==[100.0, 105.0]