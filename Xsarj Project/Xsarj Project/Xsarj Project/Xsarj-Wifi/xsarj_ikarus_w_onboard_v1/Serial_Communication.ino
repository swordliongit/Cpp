String esp_camera_local_ip = "";
String last_esp_camera_local_ip = "";

//23 ve 5 pini
void esp_to_charge_module_communication() {
  if (swSer_1.available() > 0) {
    swser1_serial_string = swSer_1.readStringUntil('\n');
    Serial.println("Serial From Charge Module: " + swser1_serial_string);
    yield();
  }
}

void swser_communication() {
  if (swSer.available() > 0) {
    swser_serial_string = swSer.readStringUntil('\n');
    Serial.println("Serial From NFC Module: " + swser_serial_string);
    yield();
  }
}

void swSer_send_Data(String swSer_String) {
  swSer.println("p_" + swSer_String + "!");
}

void swSer_send_Data_Pstatus(String swSer_String) {
  swSer.println("pst_" + swSer_String + "!");
}

//void serial2_Send_Data() {
//  Serial2.println("aaa");
//}
//
//void serial_Get_Data() {
//  if (Serial.available() > 0) {
//    data_from_serial = Serial.readStringUntil('\n');
//    yield();
//    if (data_from_serial.indexOf("mac_") == 0 && data_from_serial.indexOf("!") > 0) {
//      Serial.println("Raw Wireless Sensor Data: " + data_from_serial);
//      wireless_sensor_id = (data_from_serial.substring(data_from_serial.indexOf("id_") + 3 , data_from_serial.indexOf("bat_"))).toInt();
//      wireless_sensor_bat = (data_from_serial.substring(data_from_serial.indexOf("bat_") + 4 , data_from_serial.indexOf("!"))).toInt();
//      if (wireless_sensor_id == 1) {
//        sensor_1_value = 1;
//      }
//      if (wireless_sensor_id == 2) {
//        sensor_2_value = 1;
//      }
//      if (wireless_sensor_id == 3) {
//        sensor_3_value = 1;
//      }
//      if (wireless_sensor_id == 4) {
//        sensor_4_value = 1;
//      }
//      if (wireless_sensor_id == 5) {
//        sensor_5_value = 1;
//      }
//      if (wireless_sensor_id == 6) {
//        sensor_6_value = 1;
//      }
//      if (wireless_sensor_id == 7) {
//        sensor_7_value = 1;
//      }
//      if (wireless_sensor_id == 8) {
//        sensor_8_value = 1;
//      }
//    }
//  }
//}

//23 ve 5 pini
//void esp_To_Esp_Communication() {
//  if (swSer_1.available() > 0) {
//    second_esp_serial_data = swSer_1.readStringUntil('\n');
//    Serial.println("Data From Camera: " + second_esp_serial_data);
//    yield();
//
//    if (second_esp_serial_data.indexOf("cip_") >= 0 && second_esp_serial_data.indexOf("!") > 0) {
//      esp_camera_local_ip = second_esp_serial_data.substring(second_esp_serial_data.indexOf("cip_") + 4 , second_esp_serial_data.indexOf("!"));
//      if (last_esp_camera_local_ip != esp_camera_local_ip) {
//        last_esp_camera_local_ip = esp_camera_local_ip;
//        ademco_id = "camera-ip-detected!" + esp_camera_local_ip + "?";
//        if (wifi_Http_Post_Request_Create_Emergency(true) == 1) {
//          Serial.println("Sending To Server Camera Ip Report");
//        }
//        ademco_id = "E602-000V" + String(version);
//      }
//    }
//    if (second_esp_serial_data.indexOf("camv_") >= 0 && second_esp_serial_data.indexOf("!") > 0) {
//      camera_version = (second_esp_serial_data.substring(second_esp_serial_data.indexOf("camv_") + 5 , second_esp_serial_data.indexOf("!"))).toInt();
//      Serial.print("camera_version: ");
//      Serial.println(camera_version);
//    }
//  }
//}


//void parse_esp_second_data() {
//    if (second_esp_serial_data.indexOf("b") == 0 && second_esp_serial_data.indexOf("no_ble") > 0 && second_esp_serial_data.indexOf("s2-") < 0 && second_esp_serial_data.length() < 100) {
//    ble_status = (second_esp_serial_data.substring(second_esp_serial_data.indexOf("b") + 1 , second_esp_serial_data.indexOf("s7-"))).toInt();
//    sensor_7_value = (second_esp_serial_data.substring(second_esp_serial_data.indexOf("s7-") + 3 , second_esp_serial_data.indexOf("s8-"))).toInt();
//    sensor_8_value = (second_esp_serial_data.substring(second_esp_serial_data.indexOf("s8-") + 3 , second_esp_serial_data.indexOf("s9-"))).toInt();
//    sensor_9_value = (second_esp_serial_data.substring(second_esp_serial_data.indexOf("s9-") + 3 , second_esp_serial_data.indexOf("s10-"))).toInt();
//    sensor_10_value = (second_esp_serial_data.substring(second_esp_serial_data.indexOf("s10-") + 4 , second_esp_serial_data.indexOf("s11-"))).toInt();
//    sensor_11_value = (second_esp_serial_data.substring(second_esp_serial_data.indexOf("s11-") + 4 , second_esp_serial_data.indexOf("s12-"))).toInt();
//    sensor_12_value = (second_esp_serial_data.substring(second_esp_serial_data.indexOf("s12-") + 4 , second_esp_serial_data.indexOf("s13-"))).toInt();
//    sensor_13_value = (second_esp_serial_data.substring(second_esp_serial_data.indexOf("s13-") + 4 , second_esp_serial_data.indexOf("s14-"))).toInt();
//    sensor_14_value = (second_esp_serial_data.substring(second_esp_serial_data.indexOf("s14-") + 4 , second_esp_serial_data.indexOf("no_ble"))).toInt();
//    can_bus_working_value = 0;
//
//    //Serial.println(second_esp_serial_data);
//    //    Serial.print("ble_status: ");
//    //    Serial.print(ble_status);
//    //    Serial.print("sensor_10_value");
//    //    Serial.print(":");
//    //    Serial.println(sensor_10_value);
//  }
//
//  if (second_esp_serial_data.indexOf("b") == 0 && second_esp_serial_data.indexOf("no_ble") > 0 && second_esp_serial_data.indexOf("s2-") > 0 && second_esp_serial_data.length() < 100) {
//    ble_status = (second_esp_serial_data.substring(second_esp_serial_data.indexOf("b") + 1 , second_esp_serial_data.indexOf("s1-"))).toInt();
//    sensor_1_value = (second_esp_serial_data.substring(second_esp_serial_data.indexOf("s1-") + 3 , second_esp_serial_data.indexOf("s2-"))).toInt();
//    sensor_2_value = (second_esp_serial_data.substring(second_esp_serial_data.indexOf("s2-") + 3 , second_esp_serial_data.indexOf("s3-"))).toInt();
//    sensor_3_value = (second_esp_serial_data.substring(second_esp_serial_data.indexOf("s3-") + 3 , second_esp_serial_data.indexOf("s4-"))).toInt();
//    sensor_4_value = (second_esp_serial_data.substring(second_esp_serial_data.indexOf("s4-") + 3 , second_esp_serial_data.indexOf("s5-"))).toInt();
//    sensor_5_value = (second_esp_serial_data.substring(second_esp_serial_data.indexOf("s5-") + 3 , second_esp_serial_data.indexOf("s6-"))).toInt();
//    sensor_6_value = (second_esp_serial_data.substring(second_esp_serial_data.indexOf("s6-") + 3 , second_esp_serial_data.indexOf("s7-"))).toInt();
//    sensor_7_value = (second_esp_serial_data.substring(second_esp_serial_data.indexOf("s7-") + 3 , second_esp_serial_data.indexOf("s8-"))).toInt();
//    sensor_8_value = (second_esp_serial_data.substring(second_esp_serial_data.indexOf("s8-") + 3 , second_esp_serial_data.indexOf("s9-"))).toInt();
//    sensor_9_value = (second_esp_serial_data.substring(second_esp_serial_data.indexOf("s9-") + 3 , second_esp_serial_data.indexOf("s10-"))).toInt();
//    sensor_10_value = (second_esp_serial_data.substring(second_esp_serial_data.indexOf("s10-") + 4 , second_esp_serial_data.indexOf("s11-"))).toInt();
//    sensor_11_value = (second_esp_serial_data.substring(second_esp_serial_data.indexOf("s11-") + 4 , second_esp_serial_data.indexOf("s12-"))).toInt();
//    sensor_12_value = (second_esp_serial_data.substring(second_esp_serial_data.indexOf("s12-") + 4 , second_esp_serial_data.indexOf("s13-"))).toInt();
//    sensor_13_value = (second_esp_serial_data.substring(second_esp_serial_data.indexOf("s13-") + 4 , second_esp_serial_data.indexOf("s14-"))).toInt();
//    sensor_14_value = (second_esp_serial_data.substring(second_esp_serial_data.indexOf("s14-") + 4 , second_esp_serial_data.indexOf("no_ble"))).toInt();
//    can_bus_working_value = 1;
//
//    //Serial.println(second_esp_serial_data);
//    //    Serial.print("ble_status: ");
//    //    Serial.print(ble_status);
//    //    Serial.print("sensor_10_value");
//    //    Serial.print(":");
//    //    Serial.println(sensor_10_value);
//  }
//
//  if (second_esp_serial_data.indexOf("b") == 0 && second_esp_serial_data.indexOf("ble_con") > 0) {
//    ble_status = (second_esp_serial_data.substring(second_esp_serial_data.indexOf("b") + 1 , second_esp_serial_data.indexOf("s7-"))).toInt();
//    sensor_7_value = (second_esp_serial_data.substring(second_esp_serial_data.indexOf("s7-") + 3 , second_esp_serial_data.indexOf("s8-"))).toInt();
//    sensor_8_value = (second_esp_serial_data.substring(second_esp_serial_data.indexOf("s8-") + 3 , second_esp_serial_data.indexOf("s9-"))).toInt();
//    sensor_9_value = (second_esp_serial_data.substring(second_esp_serial_data.indexOf("s9-") + 3 , second_esp_serial_data.indexOf("s10-"))).toInt();
//    sensor_10_value = (second_esp_serial_data.substring(second_esp_serial_data.indexOf("s10-") + 4 , second_esp_serial_data.indexOf("s11-"))).toInt();
//    sensor_11_value = (second_esp_serial_data.substring(second_esp_serial_data.indexOf("s11-") + 4 , second_esp_serial_data.indexOf("s12-"))).toInt();
//    sensor_12_value = (second_esp_serial_data.substring(second_esp_serial_data.indexOf("s12-") + 4 , second_esp_serial_data.indexOf("s13-"))).toInt();
//    sensor_13_value = (second_esp_serial_data.substring(second_esp_serial_data.indexOf("s13-") + 4 , second_esp_serial_data.indexOf("s14-"))).toInt();
//    sensor_14_value = (second_esp_serial_data.substring(second_esp_serial_data.indexOf("s14-") + 4 , second_esp_serial_data.indexOf("r1-"))).toInt();
//    relay_1_cloud_value = (second_esp_serial_data.substring(second_esp_serial_data.indexOf("r1-") + 3 , second_esp_serial_data.indexOf("r2-"))).toInt();
//    relay_2_cloud_value = (second_esp_serial_data.substring(second_esp_serial_data.indexOf("r2-") + 3 , second_esp_serial_data.indexOf("r3-"))).toInt();
//    relay_3_cloud_value = (second_esp_serial_data.substring(second_esp_serial_data.indexOf("r3-") + 3 , second_esp_serial_data.indexOf("r4-"))).toInt();
//    relay_4_cloud_value = (second_esp_serial_data.substring(second_esp_serial_data.indexOf("r4-") + 3 , second_esp_serial_data.indexOf("r5-"))).toInt();
//    relay_5_cloud_value = (second_esp_serial_data.substring(second_esp_serial_data.indexOf("r5-") + 3 , second_esp_serial_data.indexOf("r6-"))).toInt();
//    relay_6_cloud_value = (second_esp_serial_data.substring(second_esp_serial_data.indexOf("r6-") + 3 , second_esp_serial_data.indexOf("r7-"))).toInt();
//    relay_7_cloud_value = (second_esp_serial_data.substring(second_esp_serial_data.indexOf("r7-") + 3 , second_esp_serial_data.indexOf("r8-"))).toInt();
//    relay_8_cloud_value = (second_esp_serial_data.substring(second_esp_serial_data.indexOf("r8-") + 3 , second_esp_serial_data.indexOf("r9-"))).toInt();
//    relay_9_cloud_value = (second_esp_serial_data.substring(second_esp_serial_data.indexOf("r9-") + 3 , second_esp_serial_data.indexOf("r10-"))).toInt();
//    relay_10_cloud_value = (second_esp_serial_data.substring(second_esp_serial_data.indexOf("r10-") + 4 , second_esp_serial_data.indexOf("r11-"))).toInt();
//    relay_11_cloud_value = (second_esp_serial_data.substring(second_esp_serial_data.indexOf("r11-") + 4 , second_esp_serial_data.indexOf("ble_con"))).toInt();
//
//    //Serial.println(second_esp_serial_data);
//    //    Serial.print("ble_status connected: ");
//    //    Serial.print(ble_status);
//    //    Serial.print("relay_16_cloud_value");
//    //    Serial.print(":");
//    //    Serial.println(relay_16_cloud_value);
//  }
//
//  if (second_esp_serial_data.indexOf("c1-") == 0 && second_esp_serial_data.indexOf("?") > 0 && second_esp_serial_data.length() > 0) {
//    config_1_value = (second_esp_serial_data.substring(second_esp_serial_data.indexOf("c1-") + 3, second_esp_serial_data.indexOf("c2-"))).toInt();
//    config_2_value = (second_esp_serial_data.substring(second_esp_serial_data.indexOf("c2-") + 3, second_esp_serial_data.indexOf("c3-"))).toInt();
//    config_3_value = (second_esp_serial_data.substring(second_esp_serial_data.indexOf("c3-") + 3, second_esp_serial_data.indexOf("c4-"))).toInt();
//    config_4_value = (second_esp_serial_data.substring(second_esp_serial_data.indexOf("c4-") + 3, second_esp_serial_data.indexOf("c5-"))).toInt();
//    config_5_value = (second_esp_serial_data.substring(second_esp_serial_data.indexOf("c5-") + 3, second_esp_serial_data.indexOf("c6-"))).toInt();
//    config_6_value = (second_esp_serial_data.substring(second_esp_serial_data.indexOf("c6-") + 3, second_esp_serial_data.indexOf("c7-"))).toInt();
//    config_7_value = (second_esp_serial_data.substring(second_esp_serial_data.indexOf("c7-") + 3, second_esp_serial_data.indexOf("c8-"))).toInt();
//    config_8_value = (second_esp_serial_data.substring(second_esp_serial_data.indexOf("c8-") + 3, second_esp_serial_data.indexOf("c9-"))).toInt();
//    config_9_value = (second_esp_serial_data.substring(second_esp_serial_data.indexOf("c9-") + 3, second_esp_serial_data.indexOf("c10-"))).toInt();
//    config_10_value = (second_esp_serial_data.substring(second_esp_serial_data.indexOf("c10-") + 4, second_esp_serial_data.indexOf("?"))).toInt();
//
//    //Serial.println(second_esp_serial_data);
//
//    change_Config_Command();
//  }
//}
