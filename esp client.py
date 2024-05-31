import asyncio
import websockets
import json
import random

y=0
x=9

def extrInt(message) :
    global ex,ey
    python_data = json.loads(message)

    ex = int(python_data["ex"])
    ey = int(python_data["ey"])
    
    print(type(ex),ex,' & ',type(ey),ey)

async def data_t_r():
    url = "ws://192.168.100.16/ws" 
    global x,y
    try:
        async with websockets.connect(url) as websocket:
            print("Connected to the WebSocket server")

            while True:
                #data2send = {"x": x,
                #           'y':y}  
                #await websocket.send(json.dumps(data2send))
                message = await websocket.recv()
                print(f"Received message: {message}")
                extrInt(message)
    
    except websockets.exceptions.ConnectionClosed as e:
        print(f"Connection closed with exception: {e}")
    except asyncio.TimeoutError:
        print("Connection attempt timed out")


asyncio.run(data_t_r())
x=100
y=50




