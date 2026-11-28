use std::net::SocketAddr;
use riskforge_service::server::router;
#[tokio::main]
async fn main() {
    let address=SocketAddr::from(
        ([127, 0, 0, 1], 9000)
    );
    let listener=tokio::net::TcpListener::bind(
        address
    ).await.unwrap();
    axum::serve(
        listener,
        router()
    ).await.unwrap();
}