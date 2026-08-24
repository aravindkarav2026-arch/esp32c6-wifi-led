#include <Arduino.h>
#include <Wire.h>

void scanI2C(int sda, int scl) {
  Serial.printf("\n--- Scanning I2C on SDA: GPIO %d | SCL: GPIO %d ---\n", sda, scl);
  
  // Enable internal pull-ups on the pins
  pinMode(sda, INPUT_PULLUP);
  pinMode(scl, INPUT_PULLUP);
  
  Wire.end(); // Reset previous I2C instance
  Wire.begin(sda, scl);

  byte error, address;
  int nDevices = 0;

  for (address = 1; address < 127; address++) {
    Wire.beginTransmission(address);
    error = Wire.endTransmission();

    if (error == 0) {
      Serial.printf("  SUCCESS! Device found at address 0x%02X\n", address);
      nDevices++;
    }
  }

  if (nDevices == 0) {
    Serial.println("  No devices found on this pair.");
  }
}

void setup() {
  Serial.begin(115200);
  delay(2000);

  // Scan Pin Pair 1: GPIO 6 & 7
  scanI2C(6, 7);
  delay(500);

  // Scan Pin Pair 2: Swapped GPIO 7 & 6
  scanI2C(7, 6);
  delay(500);

  // Scan Pin Pair 3: GPIO 2 & 3
  scanI2C(2, 3);
  delay(500);

  // Scan Pin Pair 4: Swapped GPIO 3 & 2
  scanI2C(3, 2);
}

void loop() {
  // Nothing here
}
