unsigned long previousMillis_charge_module_timer = 0;
const long interval_charge_module_timer = 1000;

void start_Charge_Data() {
  if (start_charge_data_counter == 0) {
    interface_serial.interface_send_bytes(INTERFACE_MSG_TYPE_START_CHARGE, 0);
    digitalWrite(relay_4, HIGH);
    start_charge_data_counter = 1;
  }
}

void stop_Charge_Data() {
  //Stop Charge
  interface_serial.interface_send_bytes(INTERFACE_MSG_TYPE_STOP_CHARGE, 0);
  digitalWrite(relay_4, LOW);
}


void charge_State() {
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis_charge_module_timer >= interval_charge_module_timer) {
    previousMillis_charge_module_timer = currentMillis;
    Serial.println(sensor_4_value);
    Serial.println(sensor_5_value);
    Serial.println(sensor_6_value);
    if (sensor_4_value == 0 && sensor_5_value == 4095 && sensor_6_value == 0) {
      Serial.println("Connected To Charge Module Ready To Charge");
      charge_state_from_module = 1;
      error_code_12 = "1";
    }
    if (sensor_4_value == 4095 && sensor_5_value == 4095 && sensor_6_value == 0) {
      Serial.println("Car Charging");
      charge_state_from_module = 1;
      error_code_13 = "1";
    }
    if (sensor_4_value == 0 && sensor_5_value == 4095 && sensor_6_value == 4095) {
      Serial.println("EV Charging Ventilation Requared");
      error_code_14 = "1";
    }
    if (sensor_4_value == 4095 && sensor_5_value == 0 && sensor_6_value == 0) {
      Serial.println("No Connection To Charge Module");
      charge_state_from_module = 2;
      error_code_15 = "1";
    }
    if (sensor_4_value == 4095 && sensor_5_value == 0 && sensor_6_value == 4095) {
      Serial.println("Error");
      error_code_16 = "1";
      charge_state_from_module = 2;
    }
    if (sensor_4_value == 0 && sensor_5_value == 4095 && sensor_6_value == 4095) {
      Serial.println("Unknown Error");
      error_code_17 = "1";
      charge_state_from_module = 2;
    }
  }
}
