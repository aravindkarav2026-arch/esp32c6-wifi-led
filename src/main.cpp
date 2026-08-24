#define BLYNK_TEMPLATE_ID "TMPL3pekN51Kj"
#define BLYNK_TEMPLATE_NAME "Watertanklevel"
#define BLYNK_AUTH_TOKEN "mGUWTvi_KRqoiftj8BK8YnMPn2A_9QoE"

#include <Arduino.h>
#include <WiFi.h>
#include <BlynkSimpleEsp32.h>
#include <U8g2lib.h>
#include <Wire.h>

#define RGB_PIN 8
#define SDA_PIN 2
#define SCL_PIN 3

// Replace with your Wi-Fi credentials
char ssid[] = "AKB -4G";
char pass[] = "ar20232023";

// 1.3" SH1106 I2C OLED constructor on GPIO 2 & 3
U8G2_SH1106_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, /* reset=*/ U8X8_PIN_NONE, /* clock=*/ SCL_PIN, /* data=*/ SDA_PIN);

int currentR = 0;
int currentG = 0;
int currentB = 0;

void drawScreen(const char* status) {
  u8g2.clearBuffer();
  u8g2.setFont(u8g2_font_6x10_tf);
  
  u8g2.drawStr(0, 12, "ESP32-C6 BLYNK");
  u8g2.drawHLine(0, 16, 128);
  
  u8g2.setCursor(0, 34);
  u8g2.printf("Status: %s", status);
  
  u8g2.setCursor(0, 52);
  u8g2.printf("RGB: R:%d G:%d B:%d", currentR, currentG, currentB);
  
  u8g2.sendBuffer();
}

BLYNK_WRITE(V0) {
  currentR = param[0].asInt();
  currentG = param[1].asInt();
  currentB = param[2].asInt();

  neopixelWrite(RGB_PIN, currentR, currentG, currentB);
  drawScreen("ONLINE");
}

void setup() {
  Serial.begin(115200);
  delay(1000);

  // Enable internal pull-ups on GPIO 2 and GPIO 3
  pinMode(SDA_PIN, INPUT_PULLUP);
  pinMode(SCL_PIN, INPUT_PULLUP);
  
  Wire.begin(SDA_PIN, SCL_PIN);
  Wire.setClock(100000); // Set stable 100kHz I2C bus speed

  u8g2.begin();
  drawScreen("Connecting...");

  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);
  drawScreen("ONLINE");
}

void loop() {
  Blynk.run();
}
