#include "anim.h"
#include "WiFi_connection.h"

#include <esp_task_wdt.h>
#include <SPIFFS.h>
#include <HTTPClient.h>
#include <WiFiClientSecure.h>



bool reset = true;

void setup() 
{
    Serial.begin(115200);

    // Initialize SPIFFS
    if(!SPIFFS.begin())
    {
        Serial.println("ERROR SPIFFS");
        return;
    }

    // Configure static IP address
    if(!WiFi.config(local_IP, gateway, subnet, primaryDNS))
    {
        Serial.println("STA Failed to configure");
    }

    // connect to WiFi
    connectToAP();
    delay(100);

    server.on("/", HTTP_GET, 
        [](AsyncWebServerRequest* request)
        {
            request->send(SPIFFS, "/index.html", String(), false, processor);
            if(request->params() > 0) startAnim(checkParams(request));
        }
    );
    server.on("/style.css", HTTP_GET, 
        [](AsyncWebServerRequest* request)
        {
            request->send(SPIFFS, "/style.css", "text/css");
        }
    );
    server.on("/jquery.min.js", HTTP_GET, 
        [](AsyncWebServerRequest* request)
        {
            request->send(SPIFFS, "/jquery.min.js", "text/javascript");
        }
    );

    // Start server
    server.begin();

    // start led animation
    startDisplay();
    Serial.println("Finished loading");
    
}

void loop() 
{
    esp_task_wdt_reset();
    if (Display.displayAnimate()) 
    {
        Display.displayReset();
    }

    // delay(1000);
    // selectText();
    // Serial.println(message);

    // saveText(String(millis()));
    // delay(500);
    // selectText();
    // Serial.println(message);
    // delay(500);
}


// void setup() {
 
//   Display.begin();
//   Display.setIntensity(0);
//   Display.displayClear();
// }

// void loop() {
//   Display.setTextAlignment(PA_LEFT);
//   Display.print("ESP32");
//   delay(2000);
  
//   Display.setTextAlignment(PA_CENTER);
//   Display.print("ESP32");
//   delay(2000);

//   Display.setTextAlignment(PA_RIGHT);
//   Display.print("ESP32");
//   delay(2000);

//   Display.setTextAlignment(PA_CENTER);
// //   Display.setInvert(true);
//   Display.print("ESP32");
//   delay(2000);

// //   Display.setInvert(false);
// //   delay(2000);
// }



// #include <Arduino.h>


// /***
//  * LED Blinking
//  */
// const int ledPin = 13;
// void setup() {
//     // setup pin 5 as a digital output pin
//     pinMode(ledPin, OUTPUT);
// }
// void loop() {
//     digitalWrite(ledPin, HIGH);	// turn on the LED
//     delay(100);	// wait for half a second or 500 milliseconds
//     digitalWrite(ledPin, LOW);	// turn off the LED
//     delay(100);	// wait for half a second or 500 milliseconds
// }