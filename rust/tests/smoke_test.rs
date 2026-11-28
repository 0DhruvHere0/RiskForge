use riskforge_service::health_response;
#[test]
fn health_response_is_available() {
    assert_eq!(
        health_response().status,
        "ok"
    );
}