import os
from fastapi import Header
from fastapi import HTTPException
def allowed_origins() -> list[str]:
    value=os.getenv(
        "RISKFORGE_ALLOWED_ORIGINS",
        "http://localhost:3000"
    )
    return [
        origin.strip()
        for origin in value.split(",")
        if origin.strip()
    ]
def require_api_key(
    x_api_key: str|None=Header(default=None)
):
    expected=os.getenv("RISKFORGE_API_KEY")
    if not expected:
        return
    if x_api_key!=expected:
        raise HTTPException(
            status_code=401,
            detail="invalid API key"
        )