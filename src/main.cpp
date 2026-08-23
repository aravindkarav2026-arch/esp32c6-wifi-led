#include <Arduino.h>

// Candidate pins used on Waveshare C6 boards
const int testPins[] = {0, 1, 2, 8, 12, 13, 15, 22, 23};
const int pinCount = sizeof(testPins) / sizeof(testPins[0]);

int count = 0;

void setup() {
  // Start Serial communication at 115200 baud
  Serial.begin(115200);
  delay(2000); 

  Serial.println("\n=================================");
  Serial.println(" ESP32-C6 HARDWARE & LOG TEST ");
  Serial.println("=================================");

  // Set all test pins as standard outputs
  for (int i = 0; i < pinCount; i++) {
    pinMode(testPins[i], OUTPUT);
  }
}

void loop() {
  count++;
  
  // 1. STATE HIGH / RGB ON
  Serial.printf("[%d] State: HIGH | Toggling all pins HIGH & NeoPixel RED\n", count);
  for (int i = 0; i < pinCount; i++) {
    digitalWrite(testPins[i], HIGH);
  }
  // Try built-in Arduino core RGB driving on GPIO 8
  neopixelWrite(8, 255, 0, 0); 
  
  delay(1000);

  // 2. STATE LOW / RGB OFF
  Serial.printf("[%d] State: LOW  | Toggling all pins LOW & NeoPixel OFF\n", count);
  for (int i = 0; i < pinCount; i++) {
    digitalWrite(testPins[i], LOW);
  }
  neopixelWrite(8, 0, 0, 0);
  
  delay(1000);
}
