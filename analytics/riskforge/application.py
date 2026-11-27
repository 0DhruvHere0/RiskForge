from .api import create_app
from .data.configured_provider import ConfiguredMarketDataProvider
from .data.portfolio_data import PortfolioDataService
from .portfolio_forecast import PortfolioForecaster
from .portfolio_service import PortfolioAnalysisService
def create_application(provider=None):
    selected_provider=provider or ConfiguredMarketDataProvider()
    data_service=PortfolioDataService(selected_provider)
    analysis_service=PortfolioAnalysisService(
        data_service,
        PortfolioForecaster()
    )
    return create_app(
        data_service,
        analysis_service
    )