const char * headerKeys_ota[] = {"Content-Disposition", "Date"} ;
const size_t numberOfHeaders_ota = 2;

unsigned long previousMillis_ota_request_timer = 0;
const long interval_ota_request_timer = 60000;
unsigned long ota_counter = 0;

void updateFirmware(uint8_t *data, size_t len) {
  Update.write(data, len);
  currentLength += len;
  // Print dots while waiting for update to finish
  Serial.print('.');
  // if current length of written firmware is not equal to total firmware size, repeat
  if (currentLength != totalLength) return;
  Update.end(true);
  Serial.printf("\nUpdate Success, Total Size: %u\nRebooting...\n", currentLength);
  // Restart ESP32 to see changes
  ESP.restart();
}

void wifi_Http_Get_Request_For_Ota_Filename_Setup() {
  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;
    http.begin(HOST_OF_OTA);
    http.collectHeaders(headerKeys_ota, numberOfHeaders_ota); // response daki header için
    int httpResponseCode = http.GET();

    if (httpResponseCode > 0) {
      String response = http.getString();
      Serial.println(httpResponseCode);
      Serial.println(response);
      for (int i = 0; i < http.headers(); i++) {
        Serial.println(http.header(i));
      }
      String version_name = http.header("Content-Disposition");
      if (version_name.indexOf("attachment; filename*=UTF-8''ota_xsarj_group_0001_version_") >= 0 && version_name.indexOf(".bin") >= 0) {
        http_get_version = (version_name.substring(version_name.indexOf("attachment; filename*=UTF-8''ota_xsarj_group_0001_version_") + 58, version_name.indexOf(".bin"))).toInt();
        Serial.print("http_get_version: ");
        Serial.println(http_get_version);
        ota_Setup();
      }
    } else {
      http_get_version = 9999;
      Serial.print("Error on Get Request For Getting Version Name");
      Serial.println(httpResponseCode);
    }
    http.end();
  } else {
    Serial.println("Error in WiFi connection");
  }
}


void wifi_Http_Get_Request_For_Ota_Filename() {
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis_ota_request_timer >= interval_ota_request_timer) {
    previousMillis_ota_request_timer = currentMillis;
    ota_counter++;
    if (WiFi.status() == WL_CONNECTED && ota_counter >= 720) {
      ota_counter = 0;
      HTTPClient http;
      http.begin(HOST_OF_OTA);
      http.collectHeaders(headerKeys_ota, numberOfHeaders_ota); // response daki header için
      int httpResponseCode = http.GET();

      if (httpResponseCode > 0) {
        String response = http.getString();
        Serial.println(httpResponseCode);
        Serial.println(response);
        for (int i = 0; i < http.headers(); i++) {
          Serial.println(http.header(i));
        }
        String version_name = http.header("Content-Disposition");
        if (version_name.indexOf("attachment; filename*=UTF-8''ota_xsarj_group_0001_version_") >= 0 && version_name.indexOf(".bin") >= 0) {
          http_get_version = (version_name.substring(version_name.indexOf("attachment; filename*=UTF-8''ota_xsarj_group_0001_version_") + 58, version_name.indexOf(".bin"))).toInt();
          Serial.print("http_get_version: ");
          Serial.println(http_get_version);
          ota_Restart_Esp();
        }
      } else {
        http_get_version = 9999;
        Serial.print("Error on Get Request For Getting Version Name");
        Serial.println(httpResponseCode);
      }
      http.end();
    }
  }
}

void ota_Setup() {
  // Connect to external web server
  if (version != http_get_version && http_get_version != 9999) {
    EEPROM.write(109, http_get_version);
    EEPROM.commit();
    client.begin(HOST_OF_OTA);
    // Get file, just to check if each reachable
    int resp = client.GET();
    Serial.print("Response: ");
    Serial.println(resp);
    // If file is reachable, start downloading
    if (resp == 200) {
      // get length of document (is -1 when Server sends no Content-Length header)
      totalLength = client.getSize();
      // transfer to local variable
      int len = totalLength;
      // this is required to start firmware update process
      Update.begin(UPDATE_SIZE_UNKNOWN);
      Serial.printf("FW Size: %u\n", totalLength);
      // create buffer for read
      uint8_t buff[128] = { 0 };
      // get tcp stream
      WiFiClient * stream = client.getStreamPtr();
      // read all data from server
      Serial.println("Updating firmware...");
      while (client.connected() && (len > 0 || len == -1)) {
        // get available data size
        size_t size = stream->available();
        if (size) {
          // read up to 128 byte
          int c = stream->readBytes(buff, ((size > sizeof(buff)) ? sizeof(buff) : size));
          // pass to function
          updateFirmware(buff, c);
          if (len > 0) {
            len -= c;
          }
        }
        delay(1);
      }
    } else {
      Serial.println("Cannot download firmware file. Only HTTP response 200: OK is supported. Double check firmware location #defined in HOST.");
    }
    client.end();
  }
}

void ota_Restart_Esp() {
  // Connect to external web server
  if (version != http_get_version && http_get_version != 9999) {
    // Restart ESP32 to see changes
    Serial.println("New Ota Version Found On Cloud");
    ESP.restart();
  }
}
