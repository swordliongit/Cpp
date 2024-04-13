//unsigned long previousMillis_post_req_auth = 0;
//const long interval_post_req_auth = 36000000;
//String serverName_auth = "http://185.114.21.200:8069/web/session/authenticate";
//String auth_response = "";
//
//void http_Post_Take_Session_Id() {
//  unsigned long currentMillis = millis();
//  if (currentMillis - previousMillis_post_req_auth >= interval_post_req_auth) {
//    previousMillis_post_req_auth = currentMillis;
//    if (WiFi.status() == WL_CONNECTED) {
//      HTTPClient http;
//
//      // Your Domain name with URL path or IP address with path
//      http.begin(serverName_auth);
//      http.collectHeaders(headerKeys, numberOfHeaders); // response daki header için
//
//      // Specify content-type header
//      //http.addHeader("Content-Type", "application/x-www-form-urlencoded");
//      // Data to send with HTTP POST
//      //String httpRequestData = "api_key=tPmAT5Ab3j7F9&sensor=BME280&value1=24.25&value2=49.54&value3=1005.14";
//      // Send HTTP POST request
//      //int httpResponseCode = http.POST(httpRequestData);
//
//      // If you need an HTTP request with a content type: application/json, use the following:
//      http.addHeader("Content-Type", "application/json");
//      int httpResponseCode = http.POST("{\"jsonrpc\":\"2.0\",\"params\":{\"login\":\"buyrukserhat@gmail.com\",\"password\":\"Charge.2021\",\"db\":\"Charge\"}}");
//
//
//      // If you need an HTTP request with a content type: text/plain
//      //http.addHeader("Content-Type", "text/plain");
//      //int httpResponseCode = http.POST("Hello, World!");
//
//      Serial.print("HTTP Post Response code: ");
//      Serial.println(httpResponseCode);
//
//      if (httpResponseCode > 0) {
//        auth_response = http.getString();
//        Serial.println(auth_response);
//        for (int i = 0; i < http.headers(); i++) {
//          Serial.println(http.header(i));
//        }
//        auth_session_id = http.header("Set-Cookie");
//        auth_session_id = auth_session_id.substring(0 , 51);
//        //parse_Auth_Json(auth_response); //bu satır json parse etmek için ama headerlar bir üstteki satırda alınınca gerek kalmıyor
//        Serial.print("Session Id: ");
//        Serial.println(auth_session_id);
//      }
//
//      // Free resources
//      http.end();
//    }
//  }
//}
//
//void http_Post_Take_Session_Id_Setup() {
//  if (WiFi.status() == WL_CONNECTED) {
//    HTTPClient http;
//
//    // Your Domain name with URL path or IP address with path
//    http.begin(serverName_auth);
//    http.collectHeaders(headerKeys, numberOfHeaders);
//
//    // Specify content-type header
//    //http.addHeader("Content-Type", "application/x-www-form-urlencoded");
//    // Data to send with HTTP POST
//    //String httpRequestData = "api_key=tPmAT5Ab3j7F9&sensor=BME280&value1=24.25&value2=49.54&value3=1005.14";
//    // Send HTTP POST request
//    //int httpResponseCode = http.POST(httpRequestData);
//
//    // If you need an HTTP request with a content type: application/json, use the following:
//    http.addHeader("Content-Type", "application/json");
//    int httpResponseCode = http.POST("{\"jsonrpc\":\"2.0\",\"params\":{\"login\":\"buyrukserhat@gmail.com\",\"password\":\"Charge.2021\",\"db\":\"Charge\"}}");
//
//
//    // If you need an HTTP request with a content type: text/plain
//    //http.addHeader("Content-Type", "text/plain");
//    //int httpResponseCode = http.POST("Hello, World!");
//
//    Serial.print("HTTP Post Response code: ");
//    Serial.println(httpResponseCode);
//
//    if (httpResponseCode > 0) {
//      auth_response = http.getString();
//      Serial.println(auth_response);
//      for (int i = 0; i < http.headers(); i++) {
//        Serial.println(http.header(i));
//      }
//      auth_session_id = http.header("Set-Cookie");
//      auth_session_id = auth_session_id.substring(0 , 51);
//      //parse_Auth_Json(auth_response); //bu satır json parse etmek için ama headerlar bir üstteki satırda alınınca gerek kalmıyor
//      Serial.print("Session Id: ");
//      Serial.println(auth_session_id);
//    }
//
//    // Free resources
//    http.end();
//  }
//}
//
//void parse_Auth_Json(String response) {
//  DynamicJsonBuffer  jsonBuffer(200);
//  JsonObject& root = jsonBuffer.parseObject(response);
//  if (!root.success()) {
//    Serial.println("parseObject() failed");
//  }
//  String data = root["result"]["session_id"];
//  if (data.length() > 20) {
//    auth_session_id = data;
//  }
//}
