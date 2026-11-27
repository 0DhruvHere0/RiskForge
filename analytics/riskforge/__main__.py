import os
import uvicorn
from .application import create_application
def create_server():
    return create_application()
def main():
    try:
        uvicorn.run(
            create_server(),
            host=os.getenv(
                "RISKFORGE_HOST",
                "127.0.0.1"
            ),
            port=int(
                os.getenv(
                    "RISKFORGE_PORT",
                    "8000"
                )
            )
        )
    except KeyboardInterrupt:
        pass
if __name__=="__main__":
    main()