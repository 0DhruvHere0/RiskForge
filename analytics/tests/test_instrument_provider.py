from riskforge.data.instruments import Instrument
from riskforge.data.mock_provider import InMemoryInstrumentProvider
def test_instrument_search():
    provider=InMemoryInstrumentProvider([
        Instrument(
            "RELIANCE",
            "Reliance Industries",
            "stock",
            "NSE",
            "INR"
        ),
        Instrument(
            "HDFCBANK",
            "HDFC Bank",
            "stock",
            "NSE",
            "INR"
        ),
        Instrument(
            "HDFC001",
            "HDFC Balanced Advantage Fund",
            "mutual_fund",
            "AMFI",
            "INR"
        ),
    ])
    results=provider.search("hdfc")
    assert len(results)==2
    assert results[0].symbol=="HDFCBANK"
    assert results[1].instrument_type=="mutual_fund"
def test_empty_search_result():
    provider=InMemoryInstrumentProvider([])
    assert provider.search("unknown")==[]