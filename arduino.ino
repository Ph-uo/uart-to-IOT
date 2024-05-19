
int ex,ey;
int x,y;
void uartsend(){
    // Gửi dữ liệu uart từ ESP8266 đến Arduino Due
  Serial.println(ex);
  Serial.print(",");
  Serial.print(ey);
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
      x = atoi(token); // Chuyển đổi phần tử đầu tiên thành int
      token = strtok(NULL, ",");
      if (token != NULL) {
       y = atoi(token);
      }
    }
 }
}

void setup() {
    Serial.begin(115200); 
    //Serial1.begin(9600);
}

void loop() {
  uartrecive();
  uartsend();
}
