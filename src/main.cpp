#include <Arduino.h>
#include <Adafruit_NeoPixel.h>

#define RGB_PIN 8
#define NUM_PIXELS 1

Adafruit_NeoPixel rgb(NUM_PIXELS, RGB_PIN, NEO_GRB + NEO_KHZ800);

void setup() {
  rgb.begin();
  rgb.setBrightness(40); // Brightness scale 0-255
  rgb.clear();
  rgb.show();
}

void loop() {
  // Red
  rgb.setPixelColor(0, rgb.Color(255, 0, 0));
  rgb.show();
  delay(500);

  // Green
  rgb.setPixelColor(0, rgb.Color(0, 255, 0));
  rgb.show();
  delay(500);

  // Blue
  rgb.setPixelColor(0, rgb.Color(0, 0, 255));
  rgb.show();
  delay(500);

  // Off
  rgb.setPixelColor(0, rgb.Color(0, 0, 0));
  rgb.show();
  delay(500);
}
