unsigned long previousMillis_charge_module_timer = 0;
const long interval_charge_module_timer = 1000;

unsigned long previousMillis_testcounter_timer = 0;
const long interval_testcounter_timer = 1000;

int last_charge_state_from_module = 0;

int test_counter = 0;

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

void check_charge_status() {
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis_testcounter_timer >= interval_testcounter_timer) {
    previousMillis_testcounter_timer = currentMillis;
    test_counter++;
    if (test_counter == 3 ) {
      swSer_send_Data("plugged");
    }
    if (test_counter == 60 ) {
      swSer_send_Data("unplugged");
    }

    if (test_counter == 75 ) {
      test_counter = 0;
    }
  }

  //  charge_state_from_module = 1;
  //  if (charge_state_from_module == 1 &&  last_charge_state_from_module != charge_state_from_module) {
  //    swSer_send_Data("plugged");
  //    last_charge_state_from_module = charge_state_from_module;
  //    Serial.println("Plugged Send To Esp!!!!!!!!!!!!!!");
  //  }
  //  charge_state_from_module = 2;
  //  delay(30000);
  //  if (charge_state_from_module == 2 &&  last_charge_state_from_module != charge_state_from_module) {
  //    swSer_send_Data("unplugged");
  //    last_charge_state_from_module = charge_state_from_module;
  //    Serial.println("Unplugged Send To Esp!!!!!!!!!!!!!!");
  //    delay(30000);
  //  }
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
      if (charge_counter > 0) {
        charge_cost = String(((sum_of_power / 3600) * (-1 * package_price_1)));
        relay_1_cloud_value = "0";
        relay_2_cloud_value = "0";
        relay_3_cloud_value = "0";
        control_Relays();
        Serial.println("-------------------------Charge Plug Out---------------------------");
      }
    }
    if (sensor_4_value == 4095 && sensor_5_value == 0 && sensor_6_value == 4095) {
      Serial.println("Error");
      error_code_16 = "1";
      charge_state_from_module = 2;
      Serial.println("No Connection To Charge Module");
      charge_state_from_module = 2;
      error_code_15 = "1";
      if (charge_counter > 0) {
        charge_cost = String(((sum_of_power / 3600) * (-1 * package_price_1)));
        relay_1_cloud_value = "0";
        relay_2_cloud_value = "0";
        relay_3_cloud_value = "0";
        control_Relays();
        Serial.println("-------------------------Charge Ended Up---------------------------");
      }
    }
    if (sensor_4_value == 0 && sensor_5_value == 4095 && sensor_6_value == 4095) {
      Serial.println("Unknown Error");
      error_code_17 = "1";
      charge_state_from_module = 2;
    }
    if (sensor_4_value == 0 && sensor_5_value == 0 && sensor_6_value == 0) {
      Serial.println("Unplugged Socket");
      error_code_17 = "1";
      charge_state_from_module = 2;
    }
  }
}
