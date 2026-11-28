use riskforge_service::models::PortfolioForecastRequest;
use riskforge_service::models::PortfolioHolding;
use riskforge_service::validation::validate_forecast_request;
fn valid_holding() -> PortfolioHolding {
    PortfolioHolding {
        symbol: String::from("IBM"),
        quantity: 2.0,
        purchase_price: 100.0,
        current_price: 110.0,
        drift: 0.05,
        volatility: 0.20,
    }
}
fn valid_request() -> PortfolioForecastRequest {
    PortfolioForecastRequest {
        holdings: vec![valid_holding()],
        start: String::from("2025-01-01"),
        end: String::from("2025-01-02"),
        horizon: 10.0,
        path_count: 1000,
        seed: 42,
    }
}
#[test]
fn valid_request_passes_validation() {
    assert!(
        validate_forecast_request(
            &valid_request()
        ).is_ok()
    );
}
#[test]
fn empty_holdings_are_rejected() {
    let mut request=valid_request();
    request.holdings.clear();
    assert!(
        validate_forecast_request(
            &request
        ).is_err()
    );
}
#[test]
fn invalid_path_count_is_rejected() {
    let mut request=valid_request();
    request.path_count=0;
    assert!(
        validate_forecast_request(
            &request
        ).is_err()
    );
}
#[test]
fn negative_volatility_is_rejected() {
    let mut request=valid_request();
    request.holdings[0].volatility=-0.1;
    assert!(
        validate_forecast_request(
            &request
        ).is_err()
    );
}
#[test]
fn reversed_dates_are_rejected() {
    let mut request=valid_request();
    request.start=String::from("2025-01-03");
    request.end=String::from("2025-01-02");
    assert!(
        validate_forecast_request(
            &request
        ).is_err()
    );
}