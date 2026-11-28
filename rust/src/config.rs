use std::env;
#[derive(Debug, Clone, PartialEq)]
pub struct ServiceConfig {
    pub analytics_base_url: String,
    pub analytics_api_key: Option<String>,
    pub server_host: String,
    pub server_port: u16,
}
impl ServiceConfig {
    pub fn from_values(
        analytics_base_url: impl Into<String>,
        analytics_api_key: Option<String>
    ) -> Self {
        Self {
            analytics_base_url: analytics_base_url.into(),
            analytics_api_key: analytics_api_key.filter(
                |value| !value.trim().is_empty()
            ),
            server_host: String::from("127.0.0.1"),
            server_port: 9000,
        }
    }
    pub fn from_environment() -> Self {
        let analytics_base_url=env::var(
            "RISKFORGE_ANALYTICS_URL"
        ).unwrap_or_else(
            |_| String::from("http://127.0.0.1:8000")
        );
        let analytics_api_key=env::var(
            "RISKFORGE_API_KEY"
        ).ok();
        let server_host=env::var(
            "RISKFORGE_HOST"
        ).unwrap_or_else(
            |_| String::from("127.0.0.1")
        );
        let server_port=env::var(
            "RISKFORGE_PORT"
        ).ok().and_then(
            |value| value.parse::<u16>().ok()
        ).unwrap_or(9000);
        Self {
            analytics_base_url,
            analytics_api_key: analytics_api_key.filter(
                |value| !value.trim().is_empty()
            ),
            server_host,
            server_port,
        }
    }
}