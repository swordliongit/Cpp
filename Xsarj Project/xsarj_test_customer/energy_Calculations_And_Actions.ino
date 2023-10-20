//Json To String Coverter Link: https://jsontostring.com/

unsigned long previousMillis_relay_1_timer = 0;
const long interval_relay_1_timer = 1000;

unsigned long previousMillis_plug_timer = 0;
const long interval_plug_timer = 1000;

String server_url = "http://185.114.21.200:8069";

void energy_Analyzer_Relay_1() {
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis_relay_1_timer >= interval_relay_1_timer) {
    previousMillis_relay_1_timer = currentMillis;
    if (relay_1_cloud_value == "1") {
      if (sensor_2_value > 1.5) {
        charge_counter++;
        no_charging_counter = 0;
        sum_of_power += sensor_1_value;
        //      Serial.print("charge counter: ");
        //      Serial.println(charge_counter);
        error_code_1 = "1";
        Serial.print("sum_of_power/charge_counter: ");
        Serial.println(sum_of_power / charge_counter);
      }
      if (sensor_2_value <= 1.5) {
        no_charging_counter++;
      }
    }
    if (relay_1_cloud_value == "1" && relay_1_cloud_value != relay_1_cloud_value_last) {
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
      relay_11_cloud_value = 1;
      digitalWrite(relay_11, relay_11_cloud_value.toInt());
      delay(100);
      read_Sensors();
      start_Charge_Data();
      charge_counter = 0;
      charge_cost = "0";
      sum_of_power = 0;
      start_charge_data_counter = 0;
      Serial.print("Partner Id: ");
      Serial.print(partner_id);
      Serial.print(" partner_total_payment_from_firebase: ");
      Serial.println(partner_total_payment_from_firebase);
      Serial.println("---- All Datas RESETED AND CHARGE is Started ----");
      error_code_2 = "1";
      relay_1_cloud_value_last = relay_1_cloud_value;
      relay_2_cloud_value_last = relay_2_cloud_value;
      relay_3_cloud_value_last = relay_3_cloud_value;
      if (partner_total_payment_from_firebase.toInt() > 0) {
        //wifi_Ntc_Time_Setup();
      }
    }


    if (relay_1_cloud_value == "0" && relay_1_cloud_value != relay_1_cloud_value_last) {
      relay_11_cloud_value = "0";
      charge_state_from_module = 0;
      // Arrange Current Of Evse
      control_Relays();
      stop_Charge_Data();
      digitalWrite(relay_11, relay_11_cloud_value.toInt());
      relay_1_cloud_value_last = relay_1_cloud_value;
      relay_2_cloud_value_last = relay_2_cloud_value;
      relay_3_cloud_value_last = relay_3_cloud_value;
      if (led_panel_status == 1) {
        swSer_send_Data("Xsarj Station");
      }
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

void charge_Time_plug_Out_Status() {
  if (relay_1_cloud_value == "1" && sensor_2_value < 1.5 && no_charging_counter > 60) {
    unsigned long currentMillis = millis();
    if (currentMillis - previousMillis_plug_timer >= interval_plug_timer) {
      previousMillis_plug_timer = currentMillis;
      plug_in_but_no_charge_counter++;
      if (plug_in_but_no_charge_counter == 60) {
        relay_16_cloud_value = "3"; //Plug in But No Charge
        Serial.print("Charge Alert: ");
        Serial.println("Plug is open but there is no charge");
        relay_1_cloud_value = "0";
        relay_2_cloud_value = "0";
        relay_3_cloud_value = "0";
      }
      if (plug_in_but_no_charge_counter == 180) {
        if (charge_counter >= 0) {
          charge_cost = String(((sum_of_power / 3600) * (-1 * package_price_1)));
          Serial.print("charge_cost: ");
          Serial.println(charge_cost);
          error_code_4 = "1";
          //charge_counter = 0;
          sensor_1_value = 0;
          sensor_2_value = 0;
          plug_in_but_no_charge_counter = 0;
        }
      }
    }
  }
  if (relay_1_cloud_value == "1" && sensor_2_value > 1) {
    error_code_5 = "1";
    relay_16_cloud_value = "4"; //Charge Works Well Value
  }
}

void check_Money_Finish() {
  if (charge_counter > 0 && relay_1_cloud_value == "1") {
    charge_cost = String(((sum_of_power / 3600) * (-1 * package_price_1)));
    if (-1 * charge_cost.toFloat() >= (partner_total_payment - package_price_1 - 2)) {
      relay_1_cloud_value = "0";
      relay_2_cloud_value = "0";
      relay_3_cloud_value = "0";
      control_Relays();
      error_code_6 = "1";
      Serial.println("-------------------------money_finished---------------------------");
    }
  }
}


void finish_Charge_Because_Of_Money() {
  String realtime_money_at_customer = String(partner_total_payment + (charge_counter * -0.004166));
  if (realtime_money_at_customer.toFloat() == 10.0 && relay_1_cloud_value == "1") {
    relay_15_cloud_value = "2"; //Money is going down alert
  }
  if (realtime_money_at_customer.toFloat() == 0.00 && relay_1_cloud_value == "1") {
    relay_15_cloud_value = "3"; //Money finished
    relay_1_cloud_value == "0";
    relay_2_cloud_value == "0";
    relay_3_cloud_value == "0";
  }
}
