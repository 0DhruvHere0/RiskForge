use axum::body::Body;
use axum::http::Request;
use riskforge_service::server::router;
use tower::util::ServiceExt;
#[tokio::test]
async fn health_route_returns_ok() {
    let response=router()
        .oneshot(
            Request::builder()
                .uri("/health")
                .body(Body::empty())
                .unwrap()
        )
        .await
        .unwrap();
    assert_eq!(
        response.status(),
        200
    );
}