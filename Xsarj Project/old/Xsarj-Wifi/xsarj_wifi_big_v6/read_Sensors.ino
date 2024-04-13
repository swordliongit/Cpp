unsigned long previousMillis_sensor_timer = 0;
const long interval_sensor_timer = 3000;

void read_Sensors() {
  //sensor_1_value = analogRead(sensor_1);  // sıcaklık
  //sensor_2_value = analogRead(sensor_2);  //nem
  //sensor_3_value = analogRead(sensor_3);
  sensor_4_value = analogRead(sensor_4);
  sensor_5_value = analogRead(sensor_5);
  sensor_6_value = analogRead(sensor_6);

  //sensor_7_value = analogRead(sensor_7); // analog voltage by resistor

  all_sensor_data = String(sensor_1_value) + "," + String(sensor_2_value) + "," + String(sensor_3_value) + "," + String(sensor_4_value)
                    + "," + String(sensor_5_value) + "," + String(sensor_6_value) + "," + String(sensor_7_value) + "," + String(sensor_8_value)
                    + "," + String(sensor_9_value) + "," + String(sensor_10_value) + "," + String(sensor_11_value) + "," + String(sensor_12_value)
                    + "," + String(sensor_13_value) + "," + String(sensor_14_value);

  all_sensor_values = "sv_" + String(sensor_1_value) + "," + String(sensor_2_value) + "," + String(sensor_3_value) + "," + String(sensor_4_value) + "," + String(sensor_5_value) + "," + String(sensor_6_value) + "," + String(sensor_7_value) + "," + String(sensor_8_value) + "," + String(sensor_9_value) + "," + String(plug_in_but_no_charge_counter) + "," + String(no_charging_counter) + "," + String(idle_no_charging_counter) + "," + String(charge_counter) + "lv_" + String(sum_of_power / 3600) + "ec_" + error_code_1 + error_code_2 + error_code_3 + error_code_4 + error_code_5 + error_code_6 + error_code_7 + error_code_8 + error_code_9 + error_code_10 + error_code_11 + error_code_12 + error_code_13 + error_code_14 + error_code_15 + error_code_16 + error_code_17 + "ecl_";

  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis_sensor_timer >= interval_sensor_timer) {
    previousMillis_sensor_timer = currentMillis;
    Serial.println("sensor_datas: " + all_sensor_data);

    Serial.println("--------");

    Serial.print("Relay 1 Cloud Value: ");
    Serial.println(relay_1_cloud_value);
    Serial.print("Charge Counter: ");
    Serial.println(charge_counter);
    Serial.print("No Charging Counter: ");
    Serial.println(no_charging_counter);
    Serial.print("plug_in_but_no_charge_counter: ");
    Serial.println(plug_in_but_no_charge_counter);
    Serial.print("Package Price 1: ");
    Serial.println(package_price_1);
    Serial.print("partner_total_payment: ");
    Serial.println(partner_total_payment);
    Serial.print("led_ligth_color: ");
    Serial.println(led_ligth_color);
    Serial.println("-------");
  }
}
