unsigned long previousMillis_charge_module_timer = 0;
const long interval_charge_module_timer = 1000;

void start_Charge_Data() {
  if (start_charge_data_counter == 0) {
    digitalWrite(relay_4, HIGH);
    start_charge_data_counter = 1;
  }
}

void stop_Charge_Data() {
  //Stop Charge
  digitalWrite(relay_4, LOW);
}


void charge_State() {
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis_charge_module_timer >= interval_charge_module_timer) {
    previousMillis_charge_module_timer = currentMillis;
    Serial.print("Ev Car Communication Values: ");
    Serial.print(sensor_4_value);
    Serial.print(" - ");
    Serial.print(sensor_5_value);
    Serial.print(" - ");
    Serial.println(sensor_6_value);
    if (sensor_4_value == 0 && sensor_5_value == 0 && sensor_6_value == 0) {
      Serial.println("No Connection");
      charge_status = 0;
    }
    if (sensor_4_value == 0 && sensor_5_value == 1 && sensor_6_value == 0) {
      Serial.println("Connected To Charge Module Ready To Charge");
      charge_state_from_module = 1;
      error_code_12 = "1";
      charge_status = 1;
    }
    if (sensor_4_value == 1 && sensor_5_value == 1 && sensor_6_value == 0) {
      Serial.println("Car Charging");
      charge_state_from_module = 1;
      error_code_13 = "1";
      charge_status = 2;
    }
    if (sensor_4_value == 0 && sensor_5_value == 1 && sensor_6_value == 1) {
      Serial.println("EV Charging Ventilation Requared");
      charge_state_from_module = 5;
      error_code_14 = "1";
    }
    if (sensor_4_value == 1 && sensor_5_value == 0 && sensor_6_value == 0) {
      Serial.println("No Connection To Charge Module");
      charge_state_from_module = 2;
      error_code_15 = "1";
      relay_1_cloud_value = "0";
      relay_2_cloud_value = "0";
      relay_3_cloud_value = "0";
      control_Relays();
      charge_status = 0;
      Serial.println("-------------------------Charge Plug Out---------------------------");
    }
    if (sensor_4_value == 1 && sensor_5_value == 0 && sensor_6_value == 1) {
      Serial.println("Error");
      error_code_16 = "1";
      charge_state_from_module = 6;
      error_code_15 = "1";
      relay_1_cloud_value = "0";
      relay_2_cloud_value = "0";
      relay_3_cloud_value = "0";
      control_Relays();
      Serial.println("-------------------------Charge Ended Up---------------------------");
    }
    if (sensor_4_value == 0 && sensor_5_value == 1 && sensor_6_value == 1) {
      Serial.println("Unknown Error");
      error_code_17 = "1";
      charge_state_from_module = 2;
    }
  }
}
