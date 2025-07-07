#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <SoftwareSerial.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);
SoftwareSerial espSerial(2, 3); // RX, TX

#define moisturePin A0
#define phPin A1
#define dhtPin 4
#define motorPin 5
#define buttonPin 6

float temperature, humidity;
int moisture, phValue;
bool motorOn = false;

void setup() {
  pinMode(motorPin, OUTPUT);
  pinMode(buttonPin, INPUT_PULLUP);
  digitalWrite(motorPin, LOW);

  Serial.begin(9600);
  espSerial.begin(9600);

  lcd.begin();
  lcd.backlight();
  lcd.print("Irrigation Init");
  delay(2000);
}

void loop() {
  // Read sensors
  moisture = analogRead(moisturePin);
  phValue = analogRead(phPin); // Dummy value for now

  // Simulate temp/humidity (replace with DHT sensor if available)
  temperature = 28.5;
  humidity = 45.0;

  // Check button
  if (digitalRead(buttonPin) == LOW) {
    motorOn = !motorOn;
    digitalWrite(motorPin, motorOn ? HIGH : LOW);
    delay(1000); // debounce
  }

  // Automatic control
  if (moisture < 400) {
    motorOn = true;
    digitalWrite(motorPin, HIGH);
  } else if (moisture > 700) {
    motorOn = false;
    digitalWrite(motorPin, LOW);
  }

  // Display
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Moist:");
  lcd.print(moisture);
  lcd.setCursor(0, 1);
  lcd.print("T:");
  lcd.print(temperature);
  lcd.print(" M:");
  lcd.print(motorOn ? "ON " : "OFF");

  // Send data to ESP
  String data = String(moisture) + "," + String(phValue) + "," + String(temperature) + "," + String(humidity) + "," + (motorOn ? "1" : "0");
  espSerial.println(data);

  delay(5000);
}
