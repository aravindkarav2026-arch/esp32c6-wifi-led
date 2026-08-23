#include <Arduino.h>
#include <WiFi.h>

// Replace with your Wi-Fi credentials
const char* ssid = "AKB -4G";
const char* password = "ar20232023";

// Onboard LED pin for standard ESP32-C6 boards
const int LED_PIN = 8; 

void setup() {
  Serial.begin(115200);

  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, LOW); // Start with LED OFF

  Serial.print("Connecting to Wi-Fi");
  WiFi.begin(ssid, password);
  
  // Blink LED every 250ms while attempting to connect
  while (WiFi.status() != WL_CONNECTED) {
    digitalWrite(LED_PIN, HIGH);
    delay(250);
    digitalWrite(LED_PIN, LOW);
    delay(250);
    Serial.print(".");
  }

  // Keep LED solid ON once connected
  digitalWrite(LED_PIN, HIGH); 
  
  Serial.println("\nConnected to Wi-Fi!");
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());
}

void loop() {
  // Monitor connection status continuously
  if (WiFi.status() == WL_CONNECTED) {
    digitalWrite(LED_PIN, HIGH); 
  } else {
    // Rapid alert flashing if Wi-Fi drops
    digitalWrite(LED_PIN, HIGH);
    delay(100);
    digitalWrite(LED_PIN, LOW);
    delay(100);
    WiFi.reconnect();
  }
}
