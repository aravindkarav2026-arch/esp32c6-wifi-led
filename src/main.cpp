#include <Arduino.h>

#define RGB_PIN 8

void setup() {
  Serial.begin(115200);
  delay(1000);
  Serial.println("\n--- ESP32-C6 NeoPixel Control Started ---");
}

void loop() {
  // Red
  Serial.println("Color: RED");
  neopixelWrite(RGB_PIN, 255, 0, 0);
  delay(1000);

  // Green
  Serial.println("Color: GREEN");
  neopixelWrite(RGB_PIN, 0, 255, 0);
  delay(1000);

  // Blue
  Serial.println("Color: BLUE");
  neopixelWrite(RGB_PIN, 0, 0, 255);
  delay(1000);

  // OFF
  Serial.println("Color: OFF");
  neopixelWrite(RGB_PIN, 0, 0, 0);
  delay(1000);
}
