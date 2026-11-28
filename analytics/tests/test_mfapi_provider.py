from datetime import date
import numpy as np
from riskforge.data.instruments import Instrument
from riskforge.data.mfapi_provider import MfapiProvider
class FakeMfapiClient:
    def get_json(
        self,
        endpoint: str,
        params: dict[str, str]
    ):
        assert endpoint=="mf/128628"
        return {
            "meta": {
                "scheme_code": "128628",
                "scheme_name": "HDFC Banking and PSU Debt Fund"
            },
            "data": [
                {
                    "date": "27-11-2026",
                    "nav": "100.50"
                },
                {
                    "date": "26-11-2026",
                    "nav": "100.25"
                },
                {
                    "date": "25-11-2026",
                    "nav": "100.00"
                }
            ],
            "status": "SUCCESS"
        }
def test_mfapi_history():
    provider=MfapiProvider(
        FakeMfapiClient()
    )
    instrument=Instrument(
        "128628",
        "HDFC Banking and PSU Debt Fund",
        "mutual_fund",
        "AMFI",
        "INR"
    )
    result=provider.history(
        instrument,
        date(2026, 11, 25),
        date(2026, 11, 27)
    )
    assert result.symbol=="128628"
    assert result.dates==[
        "2026-11-25",
        "2026-11-26",
        "2026-11-27"
    ]
    np.testing.assert_allclose(
        result.closes,
        np.asarray(
            [100.00, 100.25, 100.50]
        )
    )