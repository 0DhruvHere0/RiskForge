use std::net::SocketAddr;
use riskforge_service::client::AnalyticsClient;
use riskforge_service::config::ServiceConfig;
use riskforge_service::server::router_with_client;
#[tokio::main]
async fn main() {
    let config=ServiceConfig::from_environment();
    let client=AnalyticsClient::new(
        config.analytics_base_url,
        config.analytics_api_key
    );
    let address=SocketAddr::from(
        ([127, 0, 0, 1], 9000)
    );
    let listener=tokio::net::TcpListener::bind(
        address
    ).await.unwrap();
    axum::serve(
        listener,
        router_with_client(client)
    ).await.unwrap();
}