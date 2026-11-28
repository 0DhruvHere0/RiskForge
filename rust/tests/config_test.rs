use riskforge_service::config::ServiceConfig;
#[test]
fn config_uses_default_values() {
    let config=ServiceConfig::from_values(
        "http://127.0.0.1:8000",
        None
    );
    assert_eq!(
        config.analytics_base_url,
        "http://127.0.0.1:8000"
    );
    assert_eq!(
        config.analytics_api_key,
        None
    );
}
#[test]
fn config_reads_explicit_values() {
    let config=ServiceConfig::from_values(
        "http://analytics:8000",
        Some(String::from("test-secret"))
    );
    assert_eq!(
        config.analytics_base_url,
        "http://analytics:8000"
    );
    assert_eq!(
        config.analytics_api_key,
        Some(String::from("test-secret"))
    );
}
#[test]
fn empty_api_key_becomes_none() {
    let config=ServiceConfig::from_values(
        "http://analytics:8000",
        Some(String::new())
    );
    assert_eq!(
        config.analytics_api_key,
        None
    );
}