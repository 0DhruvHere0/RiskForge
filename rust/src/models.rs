use serde::{Deserialize, Serialize};
#[derive(Debug, Deserialize, Serialize, PartialEq)]
pub struct PortfolioHolding {
    pub symbol: String,
    pub quantity: f64,
    pub purchase_price: f64,
    pub current_price: f64,
    pub drift: f64,
    pub volatility: f64,
}
#[derive(Debug, Deserialize, Serialize, PartialEq)]
pub struct PortfolioForecastRequest {
    pub holdings: Vec<PortfolioHolding>,
    pub start: String,
    pub end: String,
    pub horizon: f64,
    pub path_count: usize,
    pub seed: u64,
}
#[derive(Debug, Deserialize, Serialize, PartialEq)]
pub struct PortfolioForecastResponse {
    pub expected_value: f64,
    pub lower_value: f64,
    pub median_value: f64,
    pub upper_value: f64,
}