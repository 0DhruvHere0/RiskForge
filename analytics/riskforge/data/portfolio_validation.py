import math
from .portfolio_input import PortfolioRequest
def validate_portfolio_request(request: PortfolioRequest):
    if not request.holdings:
        raise ValueError("portfolio must contain at least one holding")
    if (
        not math.isfinite(request.holding_period_years)
        or request.holding_period_years<=0.0
    ):
        raise ValueError(
            "holding_period_years must be positive and finite"
        )
    if (
        not math.isfinite(request.confidence_level)
        or request.confidence_level<=0.0
        or request.confidence_level>=1.0
    ):
        raise ValueError(
            "confidence_level must be between zero and one"
        )
    for holding in request.holdings:
        if (
            not math.isfinite(holding.purchase_price)
            or holding.purchase_price<=0.0
        ):
            raise ValueError(
                "purchase_price must be positive and finite"
            )
        if (
            not math.isfinite(holding.quantity)
            or holding.quantity<=0.0
        ):
            raise ValueError(
                "quantity must be positive and finite"
            )
    return request