use riskforge_service::errors::ErrorResponse;
#[test]
fn error_response_serializes_expected_fields() {
    let error=ErrorResponse::bad_request(
        "invalid request"
    );
    let encoded=serde_json::to_string(
        &error
    ).unwrap();
    assert!(
        encoded.contains(
            "\"error\":\"invalid_request\""
        )
    );
    assert!(
        encoded.contains(
            "\"message\":\"invalid request\""
        )
    );
}