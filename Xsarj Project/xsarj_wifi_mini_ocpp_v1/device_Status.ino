unsigned long previousMillis_charge_passive_timer = 0;
const long interval_charge_passive_timer = 3000;

void device_Status() {
  if (device_status == "active") {
    device_http_counter = 1;
    if (device_http_counter != last_device_http_counter) {
      delay(100);
      start_Charge_Data();
      relay_1_cloud_value = "1";
      relay_2_cloud_value = "1";
      relay_3_cloud_value = "1";
      charge_counter = 0;
      charge_cost = "0";
      sum_of_power = 0;
      start_charge_data_counter = 0;
      read_Sensors();
      ademco_id = "E401-000V" + String(version) + all_sensor_values;
      gsm_ademco_id = "E401-000&gsmV" + String(version) + all_sensor_values;
      wifi_Http_Post_Request_Create_Emergency(true);
      Serial.println("Ademco Send To Server E401-000 Device Active");
      last_device_http_counter = device_http_counter;
      EEPROM.write(107, int(device_http_counter));
      EEPROM.write(108, int(last_device_http_counter));
      EEPROM.commit();
    }
    ademco_id = "E602-000V" + String(version);
  }
  if (device_status == "passive") {
    device_http_counter = 0;
    if (device_http_counter != last_device_http_counter) {
      relay_1_cloud_value = "0";
      relay_2_cloud_value = "0";
      relay_3_cloud_value = "0";
      ademco_id = "R401-000V" + String(version) + all_sensor_values;
      gsm_ademco_id = "R401-000&gsmV" + String(version) + all_sensor_values;
      Serial.println("Trying To Send R401 Charge Finish Data To Cloud");
      if (wifi_Http_Post_Request_Create_Emergency(true) == 1) {
        Serial.println("Ademco Send To Server R401-000 Device Passive");
        last_device_http_counter = device_http_counter;
        EEPROM.write(107, int(device_http_counter));
        EEPROM.write(108, int(last_device_http_counter));
        EEPROM.commit();
      }
    }
    ademco_id = "E602-000V" + String(version);
  }
}



void device_Status_Setup() {
  if (device_status == "active") {
    relay_1_cloud_value = "1";
    relay_2_cloud_value = "1";
    relay_3_cloud_value = "1";
  }
  if (device_status == "passive") {
    relay_1_cloud_value = "0";
    relay_2_cloud_value = "0";
    relay_3_cloud_value = "0";
  }
}
