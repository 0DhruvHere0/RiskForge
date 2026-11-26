from datetime import date
from .pipeline import estimate_series_historical_risk
from .portfolio_input import PortfolioRequest
from .portfolio_validation import validate_portfolio_request
def analyze_portfolio_holdings(
    provider,
    request: PortfolioRequest,
    end_date: date
):
    validate_portfolio_request(request)
    results=[]
    for holding in request.holdings:
        history=provider.history(
            holding.instrument,
            holding.purchase_date,
            end_date
        )
        risk=estimate_series_historical_risk(
            history,
            request.confidence_level
        )
        results.append({
            "symbol": holding.instrument.symbol,
            "name": holding.instrument.name,
            "instrument_type": holding.instrument.instrument_type,
            "purchase_price": holding.purchase_price,
            "quantity": holding.quantity,
            "value_at_risk": risk["value_at_risk"],
            "expected_shortfall": risk["expected_shortfall"],
            "log_returns": risk["log_returns"],
        })
    return results