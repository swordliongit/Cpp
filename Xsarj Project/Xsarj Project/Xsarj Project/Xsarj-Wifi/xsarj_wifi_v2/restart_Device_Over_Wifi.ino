int rst_http_counter = 0;
int last_rst_http_counter = 0;

void restart_Device_Over_Wifi() {
  if (device_status_2 == "active") {
    rst_http_counter = 1;
    if (rst_http_counter != last_rst_http_counter) {
      ademco_id = "RST-000V" + String(version) + all_sensor_values;
      gsm_ademco_id = "RST-000&gsmV" + String(version) + all_sensor_values;
      wifi_Http_Post_Request_Create_Emergency(true);
      Serial.println("Ademco Send To Server RST-000 Restart Device Active");
      last_rst_http_counter = rst_http_counter;
      restart_device_value = 1;
    }
    ademco_id = "E602-000V" + String(version);
  }
  if (device_status_2 == "passive") {
    rst_http_counter = 0;
    if (rst_http_counter != last_rst_http_counter) {
      ademco_id = "RST-000V" + String(version) + all_sensor_values;
      gsm_ademco_id = "RST-000&gsmV" + String(version) + all_sensor_values;
      if (wifi_Http_Post_Request_Create_Emergency(true) == 1) {
        Serial.println("Ademco Send To Server RST-000 Restart Device Passive");
        last_rst_http_counter = rst_http_counter;
      }
    }
    ademco_id = "E602-000V" + String(version);
  }
}
