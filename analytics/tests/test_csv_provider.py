import numpy as np
import pytest
from riskforge.data import load_price_history_csv
def test_load_price_history_csv(tmp_path):
    path=tmp_path/"prices.csv"
    path.write_text(
        "date,close\n"
        "2025-01-01,100.0\n"
        "2025-01-02,105.0\n"
        "2025-01-03,102.0\n"
    )
    series=load_price_history_csv(path, "TEST")
    assert series.symbol=="TEST"
    assert series.dates==[
        "2025-01-01",
        "2025-01-02",
        "2025-01-03",
    ]
    np.testing.assert_array_equal(
        series.closes,
        np.array([100.0, 105.0, 102.0])
    )
def test_rejects_invalid_close(tmp_path):
    path=tmp_path/"prices.csv"
    path.write_text(
        "date,close\n"
        "2025-01-01,100.0\n"
        "2025-01-02,0.0\n"
    )
    with pytest.raises(ValueError):
        load_price_history_csv(path, "TEST")