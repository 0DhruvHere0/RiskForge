use riskforge_service::client::AnalyticsClient;
#[test]
fn forecast_endpoint_is_constructed() {
    let client=AnalyticsClient::new(
        "http://127.0.0.1:8000/",
        None
    );
    assert_eq!(
        client.endpoint(),
        "http://127.0.0.1:8000/portfolio/forecast"
    );
}