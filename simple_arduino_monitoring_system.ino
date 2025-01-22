#include <string.h>
#include <LiquidCrystal.h>

LiquidCrystal lcd(5, 4, 3, 2, A4, A5);

// Wi-Fi and API settings
String ssid     = "Simulator Wifi";
String password = "";  // No password for virtual Wi-Fi
String host     = "api.thingspeak.com";
const int httpPort   = 80;
String uri     = "/channels/1158746/fields/1.json?api_key=08OT7TXVC7502XG9&results=2";

// Pin definitions
int motor = 12;
int buz = 10;
const int soilPin = A3;    // Soil Moisture Sensor pin
const int tempPin = A2;    // TMP36 Temperature sensor pin
const int lightPin = A1;   // Photoresistor pin

// ESP8266 setup function
int setupESP8266(void) {
  Serial.begin(115200);
  Serial.println("AT");  // Begin serial communication with ESP8266
  delay(10);
  if (!Serial.find("OK")) return 1;
    
  Serial.println("AT+CWJAP=\"" + ssid + "\",\"" + password + "\"");
  delay(10);
  if (!Serial.find("OK")) return 2;

  Serial.println("AT+CIPSTART=\"TCP\",\"" + host + "\"," + httpPort);
  delay(50);
  if (!Serial.find("OK")) return 3;

  return 0;
}

// Function to read data from sensors and handle actions
void readSensors(void) {
  // Read Soil Moisture
  int soilValue = analogRead(soilPin);
  Serial.print("Soil Moisture: ");
  Serial.println(soilValue);

  // Read Temperature from TMP36
  int tempValue = analogRead(tempPin);
  float voltage = tempValue * (5.0 / 1023.0);  // Convert ADC value to voltage
  float temperature = (voltage - 0.5) * 100.0;  // Convert voltage to Celsius
  Serial.print("Temperature: ");
  Serial.print(temperature);
  Serial.println(" °C");

  // Read Light Level from Photoresistor
  int lightValue = analogRead(lightPin);
  Serial.print("Light Level: ");
  Serial.println(lightValue);

  // Display sensor data on LCD
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Soil: " + String(soilValue));
  lcd.setCursor(0, 1);
  lcd.print("Temp: " + String(temperature) + "C");
  delay(2000);  // Update every 2 seconds

  // Actuation logic for soil moisture
  if (soilValue < 500) {  // If soil is dry
    digitalWrite(motor, HIGH);  // Turn on the motor
    digitalWrite(buz, LOW);     // Turn off the buzzer
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Watering...");  // Display watering message
  } else {
    digitalWrite(motor, LOW);  // Turn off the motor
  }

  // Actuation logic for light levels
  if (lightValue < 300) {  // If light level is low
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Low light!");  // Display low light message
    delay(1000);
  }
}

// Function to send data to ThingSpeak (can be customized or omitted)
void sendDataToThingSpeak(void) {
  String httpPacket = "GET " + uri + " HTTP/1.1\r\nHost: " + host + "\r\n\r\n";
  int length = httpPacket.length();
  
  Serial.print("AT+CIPSEND=");
  Serial.println(length);
  delay(10);
  
  Serial.print(httpPacket);
  delay(10);
  
  String ch = Serial.readString();
  Serial.println(ch);
  if (!Serial.find("SEND OK\r\n")) return;
}

void setup() {
  // Initialize everything
  setupESP8266();
  pinMode(motor, OUTPUT);
  pinMode(buz, OUTPUT);
  lcd.begin(16, 2);
  lcd.setCursor(0, 0);
}

void loop() {
  // Read sensors and display values
  readSensors();
  
  // Send data to ThingSpeak (optional, can be commented out for local usage)
  sendDataToThingSpeak();

  delay(1000);  // Loop delay
}
