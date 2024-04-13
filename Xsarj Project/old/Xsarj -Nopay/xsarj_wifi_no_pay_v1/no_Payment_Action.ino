int no_payment_status = 0;
int user_plug_waiting_counter = 0;
int charge_started_value = 0;

unsigned long previousMillis_relay_closed_timer = 0;
const long interval_relay_closed_timer = 1000;

void no_payment() {
  if (charge_state_from_module == 1 && charge_started_value == 0) {
    charge_started_value = 1;
    relay_1_cloud_value = "1";
    relay_2_cloud_value = "1";
    relay_3_cloud_value = "1";
  }
  if (relay_1_cloud_value == "0") {
    unsigned long currentMillis = millis();
    if (currentMillis - previousMillis_relay_closed_timer >= interval_relay_closed_timer) {
      previousMillis_relay_closed_timer = currentMillis;
      Serial.print("user_plug_waiting_counter: ");
      Serial.println(user_plug_waiting_counter);
      charge_started_value = 0;

      delay(5000);

      relay_1_cloud_value = "1";
      relay_2_cloud_value = "1";
      relay_3_cloud_value = "1";
      
      relay_1_cloud_value_last = "0";
      relay_2_cloud_value_last = "0";
      relay_3_cloud_value_last = "0";

    }
  }

}
