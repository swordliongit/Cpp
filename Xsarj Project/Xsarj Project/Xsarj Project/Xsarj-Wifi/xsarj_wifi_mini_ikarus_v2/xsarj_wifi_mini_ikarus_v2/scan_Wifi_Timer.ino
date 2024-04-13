void scan_Wifi_Timer() {
  // WiFi.scanNetworks will return the number of networks found
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis_scan_wifi_timer >= interval_scan_wifi_timer) {
    previousMillis_scan_wifi_timer = currentMillis;
    int n = WiFi.scanNetworks();
    Serial.println("scan done");
    if (n == 0) {
      Serial.println("no networks found");
    } else {
      Serial.print(n);
      Serial.println(" networks found");
      for (int i = 0; i < n; ++i) {
        // Print SSID and RSSI for each network found
        Serial.print(i + 1);
        Serial.print(": ");
        Serial.print(WiFi.SSID(i));
        Serial.print(" (");
        Serial.print(WiFi.RSSI(i));
        Serial.print(")");
        Serial.println((WiFi.encryptionType(i) == WIFI_AUTH_OPEN) ? " " : "*");
        delay(10);
        if (WiFi.SSID(i) == ssid) {
          //ESP.restart();
          reconnect_wifi();
        }
      }
    }
  }
}
