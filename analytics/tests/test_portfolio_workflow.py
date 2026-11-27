from datetime import date
import numpy as np
from riskforge.data.models import HistoricalPriceSeries
from riskforge.data.portfolio_data import PortfolioDataService
from riskforge.data.portfolio_data import PortfolioHolding
from riskforge.data.portfolio_workflow import PortfolioWorkflow
class FakeProvider:
    def history(
        self,
        symbol: str,
        start: date,
        end: date
    ):
        return HistoricalPriceSeries(
            symbol=symbol,
            dates=["2025-01-01", "2025-01-02"],
            closes=np.asarray([100.0, 101.0])
        )
def test_load_dataset_aligns_provider_history():
    workflow=PortfolioWorkflow(
        PortfolioDataService(FakeProvider())
    )
    holdings=[
        PortfolioHolding(
            symbol="AAA",
            quantity=2.0,
            purchase_price=95.0
        )
    ]
    dataset=workflow.load_dataset(
        holdings,
        date(2025, 1, 1),
        date(2025, 1, 2)
    )
    assert dataset.dates==["2025-01-01", "2025-01-02"]
    np.testing.assert_allclose(
        dataset.closing_prices,
        np.asarray(
            [
                [100.0],
                [101.0]
            ]
        )
    )
    assert dataset.holdings==tuple(holdings)