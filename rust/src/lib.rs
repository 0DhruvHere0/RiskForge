pub mod client;
pub mod config;
pub mod models;
pub mod server;
pub mod validation;
use serde::{Deserialize, Serialize};
#[derive(Debug, Deserialize, Serialize, PartialEq)]
pub struct HealthResponse {
    pub status: String,
}
pub fn health_response() -> HealthResponse {
    HealthResponse {
        status: String::from("ok"),
    }
}