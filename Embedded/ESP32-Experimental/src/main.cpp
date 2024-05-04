#include <Arduino.h>
#include <ArduinoJson.h>
#include <HTTPClient.h>

#include <WiFi.h>
#include <HTTPClient.h>

const char *ssid = "ARTINSYSTEMS";
const char *password = "Artin2023Artin";

//Your Domain name with URL path or IP address with path
const char *server_endpoint = "https://panel.xsarj.com/led/fetch_master_wishlist";

// the following variables are unsigned longs because the time, measured in
// milliseconds, will quickly become a bigger number than can be stored in an int.
unsigned long lastTime = 0;
// Timer set to 10 minutes (600000)
//unsigned long timerDelay = 600000;
// Set timer to 5 seconds (5000)
unsigned long timerDelay = 5000;


void setup() {
    Serial.begin(115200);

    WiFi.begin(ssid, password);
    Serial.println("Connecting");
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }
    Serial.println("");
    Serial.print("Connected to WiFi network with IP Address: ");
    Serial.println(WiFi.localIP());

    // Serial.println(output);
    // Prepare JSON document
    JsonDocument doc;
    doc["count"] = 4;

    // Serialize JSON document
    char json[128];
    serializeJson(doc, json);

    WiFiClient client; // or WiFiClientSecure for HTTPS
    HTTPClient http;

    // Send request
    http.begin(server_endpoint);
    http.addHeader("Content-Type", "application/json");
    http.addHeader("Connection", "keep-alive");
    http.addHeader("Accept-Encoding", "gzip, deflate, br");
    http.addHeader("Accept", "*/*");
    http.addHeader("User-Agent", "PostmanRuntime/7.26.8");
    http.setConnectTimeout(5000);
    http.POST(json);

    // Read response
    Serial.print(http.getString());

    // Disconnect
    http.end();

    // put your setup code here, to run once:
}

void loop() {
    // put your main code here, to run repeatedly:
}
