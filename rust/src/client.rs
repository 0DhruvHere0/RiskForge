use crate::models::{
    PortfolioForecastRequest,
    PortfolioForecastResponse,
};
use reqwest::Client;
pub struct AnalyticsClient {
    client: Client,
    base_url: String,
    api_key: Option<String>,
}
impl AnalyticsClient {
    pub fn new(
        base_url: impl Into<String>,
        api_key: Option<String>
    ) -> Self {
        Self {
            client: Client::new(),
            base_url: base_url.into().trim_end_matches('/').to_string(),
            api_key,
        }
    }
    pub fn endpoint(&self) -> String {
        format!(
            "{}/portfolio/forecast",
            self.base_url
        )
    }
    pub async fn forecast(
        &self,
        request: &PortfolioForecastRequest
    ) -> Result<
        PortfolioForecastResponse,
        reqwest::Error
    > {
        let mut builder=self.client.post(
            self.endpoint()
        );
        if let Some(api_key)=&self.api_key {
            builder=builder.header(
                "X-API-Key",
                api_key
            );
        }
        builder
            .json(request)
            .send()
            .await?
            .error_for_status()?
            .json::<PortfolioForecastResponse>()
            .await
    }
}