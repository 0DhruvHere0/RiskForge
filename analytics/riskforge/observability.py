import logging
import uuid
from starlette.middleware.base import BaseHTTPMiddleware
class RequestIdMiddleware(BaseHTTPMiddleware):
    async def dispatch(self, request, call_next):
        request_id=request.headers.get(
            "X-Request-ID",
            str(uuid.uuid4())
        )
        request.state.request_id=request_id
        response=await call_next(request)
        response.headers["X-Request-ID"]=request_id
        return response
def configure_logging():
    logging.basicConfig(
        level=logging.INFO,
        format="%(asctime)s %(levelname)s %(name)s %(message)s"
    )