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
    let address=format!(
        "{}:{}",
        config.server_host,
        config.server_port
    ).parse::<SocketAddr>().unwrap();
    let listener=tokio::net::TcpListener::bind(
        address
    ).await.unwrap();
    axum::serve(
        listener,
        router_with_client(client)
    ).with_graceful_shutdown(
        shutdown_signal()
    ).await.unwrap();
}
async fn shutdown_signal() {
    tokio::signal::ctrl_c().await.unwrap();
}