/*

         _          _          _ _
        (_)        | |        | (_)
   _ __  ___  _____| | ___  __| |_
  | '_ \| \ \/ / _ \ |/ _ \/ _` | |
  | |_) | |>  <  __/ |  __/ (_| | |
  | .__/|_/_/\_\___|_|\___|\__,_|_|
  | |
  |_|
  www.pixeledi.eu
  LED-Matrix Anzeige via WEB-Server | V1.0 | 12 2021

*/

#include <WiFi.h>
#include <AsyncTCP.h>
#include "ArduinoJson.h"
#include <HTTPClient.h>
#include <ESPAsyncWebServer.h>
#include <WiFiClientSecure.h>
#include <esp_task_wdt.h>
#include <SPIFFS.h>
#include "my_text.h"
#include "my_ledmatrix.h"
#include "my_credentials.h"
#include "my_wifi.h"

unsigned long previousMillis = 0;
const long interval = 5 * 1000;
int cnt = 0;

void setup() {
  // Serial port for debugging purposes
  Serial.begin(115200);

    // Initialize SPIFFS
  if (!SPIFFS.begin()) {
    Serial.println("An Error has occurred while mounting SPIFFS");
    return;
  }

    // Configures static IP address
  if (!WiFi.config(local_IP, gateway, subnet, primaryDNS, secondaryDNS)) {
    Serial.println("STA Failed to configure");
  }

  connectToAP();
  delay(100);

  
// Route for root / web page
  server.on("/", HTTP_GET, [](AsyncWebServerRequest * request) {
    request->send(SPIFFS, "/index.html", String(), false, processor);
    changeDisplay(checkParams(request));
  });
  // Route to load style.css file
  server.on("/style.css", HTTP_GET, [](AsyncWebServerRequest * request) {
    request->send(SPIFFS, "/style.css", "text/css");
  });
    // Route to load jquery
  server.on("/jquery.min.js", HTTP_GET, [](AsyncWebServerRequest * request) {
    request->send(SPIFFS, "/jquery.min.js", "text/javascript");
  });
 // Start server
  server.begin();
  
  
  startDisplay();
  Serial.println("finished loading");
}

void loop() {
  
  //woof woof
  esp_task_wdt_reset();
   if (myDisplay.displayAnimate()) {
    myDisplay.displayReset();
  }

  /*
  speichereWert(String(millis()));
  delay(500);
  selectText();
  Serial.println(message);
  delay(500);
  */
 
/*
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= interval) {
     previousMillis = currentMillis;

     if(cnt==0) changeDisplay("rocket");
     else if(cnt==1) changeDisplay("bunny");
     else if(cnt==2) changeDisplay("ghost");
     else if(cnt==3) changeDisplay("pacman");
     else if(cnt==4) changeDisplay("walker");
     else if(cnt==5) changeDisplay("wave");
     else if(cnt==6) changeDisplay("heart");

     Serial.println(cnt);
     cnt++;

     if(cnt>=7)cnt=0;
  }
  */
 
}
