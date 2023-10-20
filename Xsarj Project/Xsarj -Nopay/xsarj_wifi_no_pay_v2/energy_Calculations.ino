//Json To String Coverter Link: https://jsontostring.com/

unsigned long previousMillis_relay_1_timer = 0;
const long interval_relay_1_timer = 1000;

unsigned long previousMillis_plug_timer = 0;
const long interval_plug_timer = 1000;

unsigned long previousMillis_idle_timer = 0;
const long interval_idle_timer = 1000;

int panel_error_message = 2;
int panel_error_message_last = 2;

void energy_Analyzer_Relay_1() {
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis_relay_1_timer >= interval_relay_1_timer) {
    previousMillis_relay_1_timer = currentMillis; 
    if (relay_1_cloud_value == "1" && relay_1_cloud_value != relay_1_cloud_value_last) {
      panel_error_message = 0;

      charge_counter = 0;
      charge_cost = "0";
      sum_of_power = 0;

      no_charging_counter = 0;
      plug_in_but_no_charge_counter = 0;
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
      delay(100);
      swSer_send_Data_Pstatus("1");
      Serial.println("---------- Master Send To Led Panel Charge Is Starting Data ---------------------");
      read_Sensors();
      start_Charge_Data();
      start_charge_data_counter = 0;
      Serial.print(partner_id);
      Serial.println("---- All Datas RESETED AND CHARGE is Started ----");
      error_code_2 = "1";
      relay_1_cloud_value_last = relay_1_cloud_value;
      relay_2_cloud_value_last = relay_2_cloud_value;
      relay_3_cloud_value_last = relay_3_cloud_value;
    }


    if (relay_1_cloud_value == "0" && relay_1_cloud_value != relay_1_cloud_value_last) {
      panel_error_message = 2;
      panel_error_message_last = panel_error_message;
      swSer_send_Data_Pstatus("4");
      Serial.println("---------- Master Send To Led Panel Finish Charge Data ---------------------");
      relay_11_cloud_value = "0";
      charge_state_from_module = 0;
      // Arrange Current Of Evse
      control_Relays();
      stop_Charge_Data();
      relay_1_cloud_value_last = relay_1_cloud_value;
      relay_2_cloud_value_last = relay_2_cloud_value;
      relay_3_cloud_value_last = relay_3_cloud_value;
      if (charge_counter >= 0) {
        charge_cost = String(((sum_of_power / 3600) * (-1 * package_price_1)));
        Serial.println("----------------------charge Finished ------------------------------: ");
        Serial.print("charge_cost: ");
        Serial.println(charge_cost);
        error_code_3 = "1";
        //charge_counter = 0;
        relay_16_cloud_value = "4"; //Charge Works Well Value
        sensor_1_value = 0;
        sensor_2_value = 0;
      }
    }
  }
}
