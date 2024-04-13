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

  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis_sensor_timer >= interval_sensor_timer) {
    previousMillis_sensor_timer = currentMillis;
    Serial.println("sensor_datas: " + all_sensor_data);
  }
}
