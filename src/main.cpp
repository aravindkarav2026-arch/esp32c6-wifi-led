#include <Arduino.h>
#include <Wire.h>
#include <U8g2lib.h>

#define SDA_PIN 6
#define SCL_PIN 7

// Standard 1.3" I2C SH1106 constructor
U8G2_SH1106_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, /* reset=*/ U8X8_PIN_NONE, /* clock=*/ SCL_PIN, /* data=*/ SDA_PIN);

void setup() {
  Serial.begin(115200);
  delay(2000);

  Serial.println("\n--- Starting I2C Scan on GPIO 6 (SDA) & GPIO 7 (SCL) ---");
  Wire.begin(SDA_PIN, SCL_PIN);

  byte error, address;
  int nDevices = 0;

  for (address = 1; address < 127; address++) {
    Wire.beginTransmission(address);
    error = Wire.endTransmission();

    if (error == 0) {
      Serial.printf("I2C device found at address 0x%02X\n", address);
      nDevices++;
    }
  }

  if (nDevices == 0) {
    Serial.println("No I2C devices found! Check wiring, power, and solder joints.");
  } else {
    Serial.println("I2C Scan Complete. Initializing Display...");
    u8g2.begin();
    u8g2.clearBuffer();
    u8g2.setFont(u8g2_font_ncenB14_tr);
    u8g2.drawStr(10, 35, "WORKING!");
    u8g2.sendBuffer();
    Serial.println("Display draw command sent.");
  }
}

void loop() {
  // Nothing here
}
