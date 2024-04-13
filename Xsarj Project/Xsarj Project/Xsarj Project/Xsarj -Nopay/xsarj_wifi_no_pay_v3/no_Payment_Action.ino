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
    Serial.println("---Charge Started---");
  }

  if (relay_1_cloud_value == "0") {
    charge_started_value = 0;
    //Serial.println("---Charge Stopped---");
  }
}
