#include <Arduino.h>
#include <WiFi.h>
#include <WebServer.h>

#define RGB_PIN 8

const char* ssid = "AKB -4G";
const char* password = "ar20232023";

WebServer server(80);

// Helper function to update the NeoPixel
void setRGB(uint8_t r, uint8_t g, uint8_t b) {
  neopixelWrite(RGB_PIN, r, g, b);
}

// Serve the HTML Control Page
void handleRoot() {
  String html = R"rawliteral(
    <!DOCTYPE html>
    <html>
    <head>
      <meta name="viewport" content="width=device-width, initial-scale=1">
      <title>ESP32-C6 RGB Control</title>
      <style>
        body { font-family: Arial, sans-serif; text-align: center; background-color: #121212; color: #ffffff; padding: 20px; }
        h1 { margin-bottom: 20px; }
        .btn-container { display: flex; flex-direction: column; gap: 15px; max-width: 300px; margin: 0 auto; }
        button { padding: 15px; font-size: 18px; border: none; border-radius: 8px; cursor: pointer; color: white; font-weight: bold; }
        .red { background-color: #e74c3c; }
        .green { background-color: #2ecc71; }
        .blue { background-color: #3498db; }
        .white { background-color: #ecf0f1; color: #000; }
        .off { background-color: #7f8c8d; }
        button:active { opacity: 0.8; }
      </style>
    </head>
    <body>
      <h1>ESP32-C6 LED Controller</h1>
      <div class="btn-container">
        <button class="red" onclick="fetch('/set?color=red')">RED</button>
        <button class="green" onclick="fetch('/set?color=green')">GREEN</button>
        <button class="blue" onclick="fetch('/set?color=blue')">BLUE</button>
        <button class="white" onclick="fetch('/set?color=white')">WHITE</button>
        <button class="off" onclick="fetch('/set?color=off')">OFF</button>
      </div>
    </body>
    </html>
  )rawliteral";
  
  server.send(200, "text/html", html);
}

// Handle LED Command Requests
void handleSet() {
  if (server.hasArg("color")) {
    String color = server.arg("color");
    if (color == "red") setRGB(255, 0, 0);
    else if (color == "green") setRGB(0, 255, 0);
    else if (color == "blue") setRGB(0, 0, 255);
    else if (color == "white") setRGB(255, 255, 255);
    else if (color == "off") setRGB(0, 0, 0);
    
    server.send(200, "text/plain", "OK");
  } else {
    server.send(400, "text/plain", "Missing color parameter");
  }
}

void setup() {
  Serial.begin(115200);
  delay(1000);

  Serial.println("\n--- ESP32-C6 Web Server Starting ---");

  // Connect to Wi-Fi
  WiFi.begin(ssid, password);
  Serial.print("Connecting to Wi-Fi");
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
    // Blink yellow while connecting
    setRGB(50, 50, 0);
    delay(100);
    setRGB(0, 0, 0);
  }

  Serial.println("\nWi-Fi Connected successfully!");
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());

  // Blink green twice to indicate successful connection
  for (int i = 0; i < 2; i++) {
    setRGB(0, 255, 0);
    delay(200);
    setRGB(0, 0, 0);
    delay(200);
  }

  // Define HTTP routes
  server.on("/", handleRoot);
  server.on("/set", handleSet);

  // Start server
  server.begin();
  Serial.println("HTTP Server Started!");
}

void loop() {
  server.handleClient();
}
