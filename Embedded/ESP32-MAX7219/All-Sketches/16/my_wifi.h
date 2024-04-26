AsyncWebServer server(80);

IPAddress local_IP(192, 168, 178, 50);
IPAddress gateway(192, 168, 178, 1);
IPAddress subnet(255, 255, 255, 0);
IPAddress primaryDNS(8, 8, 8, 8);   //optional
IPAddress secondaryDNS(8, 8, 4, 4); //optional

long btc_eur;

String processor(const String& var){
  if (var == "safedledtext") {
    return checkTextexists();
  }
}

void fetchCryptoData() {
  HTTPClient http;
  http.begin("https://api.coingecko.com/api/v3/simple/price?ids=bitcoin&vs_currencies=eur");
  int httpCode = http.GET();
  Serial.println("\nStatuscode: " + String(httpCode));
  delay(100);

  //https://arduinojson.org/v6/assistant/  
  StaticJsonDocument<2048> doc;
  String payload = http.getString();
  const char* json = payload.c_str();
  deserializeJson(doc, json);

  btc_eur = doc["bitcoin"]["eur"];  
  Serial.println(btc_eur);
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
