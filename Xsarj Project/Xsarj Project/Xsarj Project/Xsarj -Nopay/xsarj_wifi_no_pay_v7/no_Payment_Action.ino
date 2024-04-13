int no_payment_status = 0;
int user_plug_waiting_counter = 0;
int charge_started_value = 0;

unsigned long previousMillis_relay_closed_timer = 0;
const long interval_relay_closed_timer = 1000;

void no_payment() {
  //  if (charge_status == 1 && charge_started_value == 0) {
  //    charge_started_value = 1;
  //    relay_1_cloud_value = "1";
  //    relay_2_cloud_value = "1";
  //    relay_3_cloud_value = "1";
  //    Serial.println("---Charge Started---");
  //  }

  if (charge_status == 0 && last_charge_status == 0) {
    relay_1_cloud_value = "1";
    relay_2_cloud_value = "1";
    relay_3_cloud_value = "1";
    last_charge_status = charge_status;
    led_ligth_color = "white";
    Serial.println("--- Waiting For Soket To Car Connection ---");
  }

  if (charge_status == 1 && last_charge_status == 0 && charge_status != last_charge_status) {
    Serial.print("charge_status: ");
    Serial.println(charge_status);
    Serial.print("last_charge_status: ");
    Serial.println(last_charge_status);
    Serial.print("Relay 1 Cloud Value: ");
    Serial.println(relay_1_cloud_value);
    relay_1_cloud_value = "1";
    relay_2_cloud_value = "1";
    relay_3_cloud_value = "1";
    last_charge_status = charge_status;
    led_ligth_color = "green";
    Serial.println("--- Charge Started ---");
  }

  if (charge_status == 2 && last_charge_status == 1 && charge_status != last_charge_status) {
    Serial.print("charge_status: ");
    Serial.println(charge_status);
    Serial.print("last_charge_status: ");
    Serial.println(last_charge_status);
    Serial.print("Relay 1 Cloud Value: ");
    Serial.println(relay_1_cloud_value);
    relay_1_cloud_value = "1";
    relay_2_cloud_value = "1";
    relay_3_cloud_value = "1";
    last_charge_status = charge_status;
    led_ligth_color = "green";
    Serial.println("---Charge Continue---");
  }

  if (charge_status == 1 && last_charge_status == 2 && charge_status != last_charge_status) {
    Serial.print("charge_status: ");
    Serial.println(charge_status);
    Serial.print("last_charge_status: ");
    Serial.println(last_charge_status);
    Serial.print("Relay 1 Cloud Value: ");
    Serial.println(relay_1_cloud_value);
    relay_1_cloud_value = "0";
    relay_2_cloud_value = "0";
    relay_3_cloud_value = "0";
    relay_1_cloud_value_last = "0";
    control_Relays();
    last_charge_status = charge_status;
    led_ligth_color = "red";
    Serial.println("--- Charge Finished From Interior Of Car ---");
  }

  if (charge_status == 0 && last_charge_status == 1 && charge_status != last_charge_status) {
    Serial.print("charge_status: ");
    Serial.println(charge_status);
    Serial.print("last_charge_status: ");
    Serial.println(last_charge_status);
    Serial.print("Relay 1 Cloud Value: ");
    Serial.println(relay_1_cloud_value);
    relay_1_cloud_value = "0";
    relay_2_cloud_value = "0";
    relay_3_cloud_value = "0";
    last_charge_status = charge_status;
    led_ligth_color = "red";
    Serial.println("--- Plug Out ---");
  }


}
