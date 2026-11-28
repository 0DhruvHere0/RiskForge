use serde::Serialize;
#[derive(Debug, Serialize, PartialEq)]
pub struct ErrorResponse {
    pub error: String,
    pub message: String,
}
impl ErrorResponse {
    pub fn bad_request(
        message: impl Into<String>
    ) -> Self {
        Self {
            error: String::from("invalid_request"),
            message: message.into(),
        }
    }
    pub fn bad_gateway(
        message: impl Into<String>
    ) -> Self {
        Self {
            error: String::from("upstream_service_error"),
            message: message.into(),
        }
    }
}