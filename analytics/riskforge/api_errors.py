from fastapi import Request
from fastapi.responses import JSONResponse
def value_error_handler(
    request: Request,
    error: ValueError
):
    return JSONResponse(
        status_code=400,
        content={
            "error": "invalid_request",
            "message": str(error)
        }
    )
def runtime_error_handler(
    request: Request,
    error: RuntimeError
):
    return JSONResponse(
        status_code=502,
        content={
            "error": "upstream_service_error",
            "message": "market-data service unavailable"
        }
    )