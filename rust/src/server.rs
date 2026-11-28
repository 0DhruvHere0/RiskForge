use axum::routing::get;
use axum::Json;
use axum::Router;
use crate::health_response;
use crate::HealthResponse;
pub fn router() -> Router {
    Router::new().route(
        "/health",
        get(health)
    )
}
async fn health() -> Json<HealthResponse> {
    Json(health_response())
}