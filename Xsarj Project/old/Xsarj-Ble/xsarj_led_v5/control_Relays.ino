void control_Relays() {
  digitalWrite(relay_1, relay_1_cloud_value.toInt());
  digitalWrite(relay_2, relay_2_cloud_value.toInt());
  digitalWrite(relay_3, relay_3_cloud_value.toInt());
}
