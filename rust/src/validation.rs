use crate::models::{PortfolioForecastRequest, PortfolioHolding};
pub fn validate_holding(
    holding: &PortfolioHolding
) -> Result<(), String> {
    if holding.symbol.trim().is_empty() {
        return Err(String::from("symbol must not be empty"));
    }
    if !holding.quantity.is_finite() || holding.quantity<=0.0 {
        return Err(String::from("quantity must be positive and finite"));
    }
    if !holding.purchase_price.is_finite()
        || holding.purchase_price<=0.0
    {
        return Err(String::from(
            "purchase_price must be positive and finite"
        ));
    }
    if !holding.current_price.is_finite()
        || holding.current_price<=0.0
    {
        return Err(String::from(
            "current_price must be positive and finite"
        ));
    }
    if !holding.drift.is_finite() {
        return Err(String::from("drift must be finite"));
    }
    if !holding.volatility.is_finite()
        || holding.volatility<0.0
    {
        return Err(String::from(
            "volatility must be non-negative and finite"
        ));
    }
    Ok(())
}
pub fn validate_forecast_request(
    request: &PortfolioForecastRequest
) -> Result<(), String> {
    if request.holdings.is_empty() {
        return Err(String::from("holdings must not be empty"));
    }
    if request.start>request.end {
        return Err(String::from(
            "start must not be after end"
        ));
    }
    if !request.horizon.is_finite() || request.horizon<=0.0 {
        return Err(String::from(
            "horizon must be positive and finite"
        ));
    }
    if request.path_count==0 {
        return Err(String::from(
            "path_count must be positive"
        ));
    }
    for holding in &request.holdings {
        validate_holding(holding)?;
    }
    Ok(())
}