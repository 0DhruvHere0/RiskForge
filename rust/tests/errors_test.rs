use riskforge_service::errors::ErrorResponse;
#[test]
fn bad_request_error_has_expected_code() {
    assert_eq!(
        ErrorResponse::bad_request(
            "invalid portfolio"
        ),
        ErrorResponse {
            error: String::from("invalid_request"),
            message: String::from("invalid portfolio")
        }
    );
}
#[test]
fn bad_gateway_error_has_expected_code() {
    assert_eq!(
        ErrorResponse::bad_gateway(
            "analytics unavailable"
        ),
        ErrorResponse {
            error: String::from("upstream_service_error"),
            message: String::from("analytics unavailable")
        }
    );
}