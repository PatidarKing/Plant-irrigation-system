#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>

const char* ssid = "Your_SSID";
const char* password = "Your_PASSWORD";
const char* server = "http://your-server-ip/insert.php";

String incomingData = "";

void setup() {
  Serial.begin(9600);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
  }
}

void loop() {
  if (Serial.available()) {
    incomingData = Serial.readStringUntil('\n');
    sendData(incomingData);
  }
  delay(5000);
}

void sendData(String data) {
  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;
    http.begin(server);
    http.addHeader("Content-Type", "application/x-www-form-urlencoded");

    // Data format: moisture,ph,temp,hum,motor
    int m = 0, p = 0, t = 0, h = 0, mo = 0;
    sscanf(data.c_str(), "%d,%d,%d,%d,%d", &m, &p, &t, &h, &mo);
    String postData = "moisture=" + String(m) + "&ph=" + String(p) + "&temp=" + String(t) + "&humidity=" + String(h) + "&motor=" + String(mo);

    int code = http.POST(postData);
    http.end();
  }
}
