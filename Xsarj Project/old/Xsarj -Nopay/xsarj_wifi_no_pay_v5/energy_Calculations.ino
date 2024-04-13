//Json To String Coverter Link: https://jsontostring.com/

unsigned long previousMillis_relay_1_timer = 0;
const long interval_relay_1_timer = 1000;

unsigned long previousMillis_plug_timer = 0;
const long interval_plug_timer = 1000;

unsigned long previousMillis_idle_timer = 0;
const long interval_idle_timer = 1000;

void energy_Analyzer_Relay_1() {
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis_relay_1_timer >= interval_relay_1_timer) {
    previousMillis_relay_1_timer = currentMillis;
    if (relay_1_cloud_value == "1" && relay_1_cloud_value != relay_1_cloud_value_last) {
      start_charge_data_counter = 0;
      delay(100);
      start_Charge_Data();
      Serial.println("---- All Datas RESETED AND CHARGE is Started ----");
      error_code_2 = "1";
      relay_1_cloud_value_last = relay_1_cloud_value;
      relay_2_cloud_value_last = relay_2_cloud_value;
      relay_3_cloud_value_last = relay_3_cloud_value;
    }


    if (relay_1_cloud_value == "0" && relay_1_cloud_value != relay_1_cloud_value_last) {
      Serial.println("---------- Master Send To Led Panel Finish Charge Data ---------------------");
      charge_state_from_module = 0;
      control_Relays();
      stop_Charge_Data();
      relay_1_cloud_value_last = relay_1_cloud_value;
      relay_2_cloud_value_last = relay_2_cloud_value;
      relay_3_cloud_value_last = relay_3_cloud_value;
      Serial.println("----------------------charge Finished ------------------------------: ");
      delay(60000);
      relay_1_cloud_value = "1";
      relay_2_cloud_value = "1";
      relay_3_cloud_value = "1";
    }
  }
}
