#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>

// WiFi Configuration (Wokwi open network)
const char* ssid = "Wokwi-GUEST";
const char* password = "";

// Hardware Pins
const int BUTTON_PIN = 12;
const int LED_GREEN = 2;
const int LED_RED = 4;

// API Endpoint (CoinGecko public API for Bitcoin price in USD)
const char* api_url = "https://api.coingecko.com/api/v3/simple/price?ids=bitcoin&vs_currencies=usd&include_24hr_change=true";

void setup() {
  Serial.begin(115200);
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  pinMode(LED_GREEN, OUTPUT);
  pinMode(LED_RED, OUTPUT);

  // Connect to Wokwi WiFi
  WiFi.begin(ssid, password);
  Serial.print("Connecting to WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nWiFi Connected!");
  
  // Initial Fetch
  fetchAssetData();
}

void fetchAssetData() {
  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;
    http.begin(api_url);
    
    int httpCode = http.GET();
    if (httpCode > 0) {
      String payload = http.getString();
      Serial.println("\n[API Response Payload]:");
      Serial.println(payload);

      // Parse JSON
      StaticJsonDocument<512> doc;
      DeserializationError error = deserializeJson(doc, payload);

      if (!error) {
        float price = doc["bitcoin"]["usd"];
        float change24h = doc["bitcoin"]["usd_24h_change"];

        Serial.println("=================================");
        Serial.print("Asset: Bitcoin (BTC)\n");
        Serial.print("Current Price: $");
        Serial.println(price, 2);
        Serial.print("24h Change: ");
        Serial.print(change24h, 2);
        Serial.println("%");
        Serial.println("=================================");

        if (change24h >= 0) {
          digitalWrite(LED_GREEN, HIGH);
          digitalWrite(LED_RED, LOW);
        } else {
          digitalWrite(LED_GREEN, LOW);
          digitalWrite(LED_RED, HIGH);
        }
      } else {
        Serial.print("JSON Parsing failed: ");
        Serial.println(error.f_str());
      }
    } else {
      Serial.print("HTTP Request failed, error: ");
      Serial.println(http.errorToString(httpCode).c_str());
    }
    http.end();
  }
}

void loop() {
  // Manual trigger button check
  if (digitalRead(BUTTON_PIN) == LOW) {
    Serial.println("\nButton pressed! Fetching latest market data...");
    fetchAssetData();
    delay(1000); // Debounce delay
  }
  delay(100);
}
