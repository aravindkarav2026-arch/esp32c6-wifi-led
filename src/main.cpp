#include <Arduino.h>
#include <WiFi.h>
#include <Adafruit_NeoPixel.h>

const char* ssid = "YOUR_WIFI_NAME";
const char* password = "YOUR_WIFI_PASSWORD";

// Waveshare ESP32-C6 onboard RGB LED is on GPIO 8
#define RGB_PIN 8
#define NUM_PIXELS 1

Adafruit_NeoPixel rgb(NUM_PIXELS, RGB_PIN, NEO_GRB + NEO_KHZ800);

void setup() {
  Serial.begin(115200);

  rgb.begin();
  rgb.setBrightness(30); // Set low brightness (0-255) to avoid harsh light
  rgb.clear();
  rgb.show();

  WiFi.begin(ssid, password);
  Serial.print("Connecting to Wi-Fi");

  // Blink BLUE while connecting to Wi-Fi
  while (WiFi.status() != WL_CONNECTED) {
    rgb.setPixelColor(0, rgb.Color(0, 0, 255)); // Blue ON
    rgb.show();
    delay(250);

    rgb.setPixelColor(0, rgb.Color(0, 0, 0));   // OFF
    rgb.show();
    delay(250);

    Serial.print(".");
  }

  // Solid GREEN once Wi-Fi is connected
  rgb.setPixelColor(0, rgb.Color(0, 255, 0)); // Green ON
  rgb.show();

  Serial.println("\nConnected to Wi-Fi!");
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());
}

void loop() {
  if (WiFi.status() != WL_CONNECTED) {
    // Flash RED if Wi-Fi disconnects
    rgb.setPixelColor(0, rgb.Color(255, 0, 0)); // Red
    rgb.show();
    delay(100);
    rgb.setPixelColor(0, rgb.Color(0, 0, 0));
    rgb.show();
    delay(100);
    WiFi.reconnect();
  } else {
    // Keep solid GREEN when healthy
    rgb.setPixelColor(0, rgb.Color(0, 255, 0));
    rgb.show();
    delay(1000);
  }
}
