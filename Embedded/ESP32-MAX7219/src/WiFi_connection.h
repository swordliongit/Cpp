#ifndef WIFI_CONNECTION_H
#define WIFI_CONNECTON_H


#include "credentials.h"
#include "textfile.h"

#include <WiFi.h>
#include <ESPAsyncWebServer.h>
#include <AsyncTCP.h>


// setup the ESP-32 server
AsyncWebServer server(80);
IPAddress local_IP(192, 168, 100, 50);
IPAddress gateway(192, 168, 100, 1);
IPAddress subnet(255, 255, 255, 0);
IPAddress primaryDNS(8, 8, 8, 8); // optional
IPAddress secondaryDNS(8, 8, 4, 4); // optional

String processor(const String& var)
{
    if(var == "savedledtext")
    {
        return checkTextexists();
    }
}

String checkParams(AsyncWebServerRequest* request)
{
    if(request->hasParam("ledtext"))
    {
        saveText(request->getParam("ledtext")->value());
    }
    return "ledtext";
}

void connectToAP()
{
    WiFi.begin(ssid, password);
    while(WiFi.status() != WL_CONNECTED)
    {
        delay(1000);
        Serial.println("Connecting to WiFi...");
    }
    Serial.println(WiFi.localIP());
}

#endif