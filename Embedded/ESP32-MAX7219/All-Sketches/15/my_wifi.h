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
  if (request->hasParam("ledtext")) {
    speichereWert(request->getParam("ledtext")->value());
    return "ledtext";
  }
  else if (request->hasParam("rocket")) {
    speichereWert(request->getParam("rocket")->value());
    return "rocket";
  }
  else if (request->hasParam("walker")) {
  
    speichereWert(request->getParam("walker")->value());
    return "walker";
  }
  else if (request->hasParam("pacman")) {

    speichereWert(request->getParam("pacman")->value());
    return "pacman";
  }
  else if (request->hasParam("heart")) {
    speichereWert(request->getParam("heart")->value());
    return "heart";
  }
  else if (request->hasParam("wave")) {
    speichereWert(request->getParam("wave")->value());
    return "wave";
  }

  else if (request->hasParam("ghost")) {
    speichereWert(request->getParam("ghost")->value());
    return "ghost";
  }

   else if (request->hasParam("bunny")) {
    speichereWert(request->getParam("bunny")->value());
    return "bunny";
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
