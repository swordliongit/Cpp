int frr_http_counter = 0;
int last_frr_http_counter = 0;

void fast_Response_Request() {
  if (device_status_3 == "active") {
    frr_http_counter = 1;
    if (frr_http_counter != last_frr_http_counter) {
      ademco_id = "FRR-000V" + String(version) + all_sensor_values;
      gsm_ademco_id = "FRR-000&gsmV" + String(version) + all_sensor_values;
      wifi_Http_Post_Request_Create_Emergency(true);
      Serial.println("Ademco Send To Server FRR-000 Fast Request Response Active");
      last_frr_http_counter = frr_http_counter;
    }
    ademco_id = "E602-000V" + String(version);
  }
  if (device_status_3 == "passive") {
    frr_http_counter = 0;
    if (frr_http_counter != last_frr_http_counter) {
      ademco_id = "FRR-000V" + String(version) + all_sensor_values;
      gsm_ademco_id = "FRR-000&gsmV" + String(version) + all_sensor_values;
      if (wifi_Http_Post_Request_Create_Emergency(true) == 1) {
        Serial.println("Ademco Send To Server FRR-000 Fast Request Response Passive");
        last_frr_http_counter = frr_http_counter;
      }
    }
    ademco_id = "E602-000V" + String(version);
  }
}
