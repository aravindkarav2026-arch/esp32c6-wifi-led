#define BLYNK_TEMPLATE_ID "TMPL3pekN51Kj"
#define BLYNK_TEMPLATE_NAME "Watertanklevel"
#define BLYNK_AUTH_TOKEN "mGUWTvi_KRqoiftj8BK8YnMPn2A_9QoE"

#include <Arduino.h>
#include <WiFi.h>
#include <BlynkSimpleEsp32.h>

#define RGB_PIN 8

// Replace with your Wi-Fi credentials
char ssid[] = "AKB -4G";
char pass[] = "ar20232023";

// Receives RGB values from Blynk app / Dashboard widget assigned to V0
BLYNK_WRITE(V0) {
  int r = param[0].asInt();
  int g = param[1].asInt();
  int b = param[2].asInt();

  neopixelWrite(RGB_PIN, r, g, b);
  Serial.printf("Blynk RGB Updated -> R: %d, G: %d, B: %d\n", r, g, b);
}

void setup() {
  Serial.begin(115200);
  delay(1000);

  Serial.println("\n=================================");
  Serial.println(" ESP32-C6 BLYNK CONNECT START ");
  Serial.println("=================================");

  // Connects to Wi-Fi and Blynk Cloud
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);

  // Quick green flash to signal online status
  neopixelWrite(RGB_PIN, 0, 255, 0);
  delay(500);
  neopixelWrite(RGB_PIN, 0, 0, 0);
}

void loop() {
  Blynk.run();
}
