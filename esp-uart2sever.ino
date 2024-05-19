#include <ArduinoJson.h>
#include <WiFi.h>
#include <ESPAsyncWebServer.h>
#include <AsyncTCP.h>
#include <SimpleTimer.h>

int ex,ey;//data tu due
int x,y;//data tu python
const char* ssid = "esp32";
const char* password = "12345678";

// Create an AsyncWebServer object on port 80
AsyncWebServer server(80);
AsyncWebSocket ws("/ws");
SimpleTimer timer;  

// send to the WebSocket client-gửi dữ liệu đến client qua websocket
void send2client() {
  StaticJsonDocument<200> jsonDoc;
  jsonDoc["ex"] = ex; // gia tri de gui di
  jsonDoc["ey"] = ey;    
  String jsonString;
  serializeJson(jsonDoc, jsonString);
  ws.textAll(jsonString);
}

// WebSocket event handler
void onWebSocketEvent(AsyncWebSocket *server, AsyncWebSocketClient *client, AwsEventType type, void *arg, uint8_t *data, size_t len) {
  if (type == WS_EVT_CONNECT) {
    Serial.println("WebSocket client connected");
    client->ping();
  } else if (type == WS_EVT_DISCONNECT) {
    Serial.println("WebSocket client disconnected");
  } else if (type == WS_EVT_DATA) {
    Serial.println("WebSocket data received");
    String message = (char*)data;
    if (message == "getReadings") {
      send2client();
    }
  }
}

void uartsend(){
  // Gửi dữ liệu uart từ ESP32 đến Arduino Due
  Serial.println(x);
  Serial.print(",");
  Serial.print(y);
}
void uartrecive(){
 if (Serial.available() > 0) {
    // Đọc một dòng từ UART
    String inputString = Serial.readStringUntil('\n');
    inputString.trim();

    // Chuyển chuỗi thành mảng ký tự
    char inputChars[inputString.length() + 1];
    inputString.toCharArray(inputChars, inputString.length() + 1);

    // Tách chuỗi thành hai phần tử x và y
    char *token = strtok(inputChars, ",");
    if (token != NULL) {
      ex = atoi(token); 
      token = strtok(NULL, ",");
      if (token != NULL) {
        ey = atoi(token);
      }
    }
 }
}

void setup() {
  // Start the Serial Monitor
  Serial.begin(115200);
  // start network-khởi tạo network của esp32
  WiFi.softAP(ssid, password);

  // Attach WebSocket event handler-khởi tạo websocket
  ws.onEvent(onWebSocketEvent);
  server.addHandler(&ws);

  // Start the server-khởi tạo sever
  Serial.println("IP address: ");
  Serial.println(WiFi.softAPIP());
  server.begin();

// send data on 100 milisec period- gửi data mỗi 100 mili giây
  timer.setInterval(100, send2client); 
}

void loop() {
  timer.run(); // Run the timer
  uartsend();
  uartrecive();

}


