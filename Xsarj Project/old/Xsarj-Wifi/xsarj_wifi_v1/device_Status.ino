void device_Status() {
  if (device_status == "active") {
    device_http_counter = 1;
    if (device_http_counter != last_device_http_counter) {
      relay_1_cloud_value = "1";
      relay_2_cloud_value = "1";
      relay_3_cloud_value = "1";
      no_charging_counter = 0;
      plug_in_but_no_charge_counter = 0;
      idle_no_charging_counter = 0;
      error_code_1 = "0";
      error_code_2 = "0";
      error_code_3 = "0";
      error_code_4 = "0";
      error_code_5 = "0";
      error_code_6 = "0";
      error_code_7 = "0";
      error_code_8 = "0";
      error_code_9 = "0";
      error_code_10 = "0";
      error_code_11 = "0";
      error_code_12 = "0";
      error_code_13 = "0";
      error_code_14 = "0";
      error_code_15 = "0";
      error_code_16 = "0";
      error_code_17 = "0";
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
      ademco_id = "R401-000V" + String(version) + all_sensor_values;
      gsm_ademco_id = "R401-000&gsmV" + String(version) + all_sensor_values;
      if (wifi_Http_Post_Request_Create_Emergency(true) == 1) {
        Serial.println("Ademco Send To Server R401-000 Device Passive");
        last_device_http_counter = device_http_counter;
        EEPROM.write(107, int(device_http_counter));
        EEPROM.write(108, int(last_device_http_counter));
        EEPROM.commit();
        relay_1_cloud_value = "0";
        relay_2_cloud_value = "0";
        relay_3_cloud_value = "0";
        partner_total_payment = 0;
      }
    }
    ademco_id = "E602-000V" + String(version);
  }
}
