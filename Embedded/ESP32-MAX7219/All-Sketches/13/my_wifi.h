AsyncWebServer server(80);

IPAddress local_IP(192, 168, 178, 50);
IPAddress gateway(192, 168, 178, 1);
IPAddress subnet(255, 255, 255, 0);
IPAddress primaryDNS(8, 8, 8, 8);   //optional
IPAddress secondaryDNS(8, 8, 4, 4); //optional

String processor(const String& var){
  if (var == "safedledtext") {
    return checkTextexists();
  }
}

String checkParams(AsyncWebServerRequest *request){
    if(request->hasParam("ledtext")){
      speichereWert(request->getParam("ledtext")->value());
      return "ledtext";
    }
}

void connectToAP() {
  // Connect to Wi-Fi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi..");
  }
  Serial.println(WiFi.localIP());
}
