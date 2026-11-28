use riskforge_service::models::PortfolioForecastRequest;
use riskforge_service::models::PortfolioForecastResponse;
use riskforge_service::models::PortfolioHolding;
#[test]
fn portfolio_request_round_trips_through_json() {
    let request=PortfolioForecastRequest {
        holdings: vec![
            PortfolioHolding {
                symbol: String::from("IBM"),
                quantity: 2.0,
                purchase_price: 100.0,
                current_price: 110.0,
                drift: 0.05,
                volatility: 0.20,
            }
        ],
        start: String::from("2025-01-01"),
        end: String::from("2025-01-02"),
        horizon: 10.0,
        path_count: 1000,
        seed: 42,
    };
    let encoded=serde_json::to_string(&request).unwrap();
    let decoded: PortfolioForecastRequest=
        serde_json::from_str(&encoded).unwrap();
    assert_eq!(decoded, request);
}
#[test]
fn portfolio_response_serializes_expected_values() {
    let response=PortfolioForecastResponse {
        expected_value: 120.0,
        lower_value: 80.0,
        median_value: 115.0,
        upper_value: 160.0,
    };
    let encoded=serde_json::to_string(&response).unwrap();
    assert!(encoded.contains("\"expected_value\":120.0"));
}