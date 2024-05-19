import asyncio
import websockets
import json

def extrInt(message) :
    global x,y
    python_data = json.loads(message)

    x = int(python_data["temperature"])
    y = int(python_data["humidity"])
    
    print(type(x))
    print(x)
    print(type(y))
    print(y)

async def receive_data():
    url = "ws://192.168.4.1/ws" 

    try:
        async with websockets.connect(url) as websocket:
            print("Connected to the WebSocket server")

            while True:
                message = await websocket.recv()
                print(f"Received message: {message}")
                extrInt(message)

    except websockets.exceptions.ConnectionClosed as e:
        print(f"Connection closed with exception: {e}")
    except asyncio.TimeoutError:
        print("Connection attempt timed out")


if __name__ == "__main__":
    asyncio.run(receive_data())
    #extrInt(message)        





