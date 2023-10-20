String last_device_status_4 = "passive";

void control_Lamp() {
  if (device_status_4 == "active" && last_device_status_4 != device_status_4) {
    last_device_status_4 = device_status_4;
    relay_5_cloud_value = "0"; // lamp LAMP
    control_Relays();
    ademco_id = "lamp-activated";
    if (wifi_Http_Post_Request_Create_Emergency(true) == 1) {
      Serial.println("Sending To Server lamp-activated Report");
    }
    ademco_id = "E602-000V" + String(version);
  }
  if (device_status_4 == "passive" && last_device_status_4 != device_status_4) {
    last_device_status_4 = device_status_4;
    relay_5_cloud_value = "1"; // lamp LAMP
    control_Relays();
    ademco_id = "lamp-disabled";
    if (wifi_Http_Post_Request_Create_Emergency(true) == 1) {
      Serial.println("Sending To Server lamp-disabled Report");
    }
    ademco_id = "E602-000V" + String(version);
  }
}
