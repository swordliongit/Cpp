String last_device_status_1 = "passive";

void control_camera() {
  if (device_status_1 == "active" && last_device_status_1 != device_status_1) {
    last_device_status_1 = device_status_1;
    swSer_1.println("camera_activated");
    ademco_id = "camera-activated";
    if (wifi_Http_Post_Request_Create_Emergency(true) == 1) {
      Serial.println("Sending To Server camera-activated Report");
    }
    ademco_id = "E602-000V" + String(version);
  }
  if (device_status_1 == "passive" && last_device_status_1 != device_status_1) {
    last_device_status_1 = device_status_1;
    swSer_1.println("camera_disabled");
    ademco_id = "camera-disabled";
    if (wifi_Http_Post_Request_Create_Emergency(true) == 1) {
      Serial.println("Sending To Server camera-disabled Report");
    }
    ademco_id = "E602-000V" + String(version);
  }
}
