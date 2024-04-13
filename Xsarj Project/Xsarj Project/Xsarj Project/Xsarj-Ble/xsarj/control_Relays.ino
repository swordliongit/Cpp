void control_Relays() {
//  if (sensor_7_value < 1) {
//    digitalWrite(relay_1, HIGH);
//  }
//  if (sensor_7_value >= 1) {
//    digitalWrite(relay_1, LOW);
//  }
  digitalWrite(relay_1, relay_1_cloud_value.toInt());
    
  if (humidity_manuel_auto_value == 0) {
    digitalWrite(relay_2, relay_2_cloud_value.toInt());
  }
  if (fan_manuel_auto_value == 0) {
    digitalWrite(relay_3, relay_3_cloud_value.toInt());
  }

  if (water_manuel_auto == 1 || water_manuel_auto == 0) {
    digitalWrite(relay_4, relay_4_cloud_value.toInt());
    digitalWrite(relay_5, relay_5_cloud_value.toInt());
    digitalWrite(relay_6, relay_6_cloud_value.toInt());
    digitalWrite(relay_7, relay_7_cloud_value.toInt());
    digitalWrite(relay_8, relay_8_cloud_value.toInt());
    digitalWrite(relay_9, relay_9_cloud_value.toInt());
    digitalWrite(relay_10, relay_10_cloud_value.toInt());
    digitalWrite(relay_11, relay_11_cloud_value.toInt());
  }
}
