use std::sync::Arc;
use axum::extract::State;
use axum::http::StatusCode;
use axum::routing::get;
use axum::routing::post;
use axum::Json;
use axum::Router;
use crate::client::AnalyticsClient;
use crate::health_response;
use crate::models::PortfolioForecastRequest;
use crate::models::PortfolioForecastResponse;
use crate::validation::validate_forecast_request;
use crate::HealthResponse;
pub fn router() -> Router {
    Router::new().route(
        "/health",
        get(health)
    )
}
pub fn router_with_client(
    client: AnalyticsClient
) -> Router {
    Router::new()
        .route(
            "/health",
            get(health)
        )
        .route(
            "/portfolio/forecast",
            post(forecast)
        )
        .with_state(
            Arc::new(client)
        )
}
async fn health() -> Json<HealthResponse> {
    Json(health_response())
}
async fn forecast(
    State(client): State<Arc<AnalyticsClient>>,
    Json(request): Json<PortfolioForecastRequest>
) -> Result<
    Json<PortfolioForecastResponse>,
    StatusCode
> {
    validate_forecast_request(
        &request
    ).map_err(
        |_| StatusCode::BAD_REQUEST
    )?;
    let response=client.forecast(
        &request
    ).await.map_err(
        |_| StatusCode::BAD_GATEWAY
    )?;
    Ok(Json(response))
}