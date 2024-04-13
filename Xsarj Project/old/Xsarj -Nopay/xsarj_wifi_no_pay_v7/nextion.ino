//unsigned long previousMillis_send_data_nextion = 0;
//const long interval_send_data_nextion = 5000;
//int nextion_test_counter = 0;
//String heart_beat_value = "";
//
//int wifi_reset_counter = 0;
//
//int pause_counter = 0;
//
//void nextion_Control() {
//  String message = myNextion.listen();
//  if (message != "") { // if a message is received...
//    //if (message.indexOf("&") >= 0 && message.indexOf("!") >= 0) { // if a message is received...
//    //  second_esp_serial_data.substring(second_esp_serial_data.indexOf("id_") + 3 , second_esp_serial_data.indexOf("bat_"))
//    Serial.println(message); //...print it out
//    nextion_Send_Data_After_Take(message);
//  }
//}
//
//void nextion_Send_Datas_At_Setup() {
//  myNextion.setComponentValue("x3", int(entrance_delay_time * 10));
//  myNextion.setComponentValue("n1", camera_version);
//  myNextion.setComponentValue("n3", version);
//  if (device_status == "active") {
//    myNextion.sendCommand("b13.txt=\"||\"");
//  }
//}
//
//void nextion_Send_Data_Periodic() {
//  if (ekg_active_value == 1) {
//    heart_beat_value = "add 1,0," + String(sensor_2_value);
//    myNextion.sendCommand(heart_beat_value.c_str());
//  }
//  //myNextion.setComponentValue("n1_human", 12);
//
//  if (ekg_active_value == 0) {
//    unsigned long currentMillis = millis();
//    if (currentMillis - previousMillis_send_data_nextion >= interval_send_data_nextion) {
//      previousMillis_send_data_nextion = currentMillis;
//      myNextion.setComponentValue("x0", int((temperature * 100) / 10));
//      myNextion.setComponentValue("x1", int((humidity * 100) / 10));
//      myNextion.setComponentValue("n1", camera_version);
//      myNextion.setComponentValue("n3", version);
//      myNextion.setComponentValue("x3", int(entrance_delay_time * 10));
//      if (device_status == "active") {
//        myNextion.sendCommand("b6.txt=\"Bitir\"");
//      }
//      if (device_status == "passive") {
//        myNextion.sendCommand("b6.txt=\"Aktif Et\"");
//      }
//      if (zone_status_2 == true) {
//        myNextion.setComponentValue("x2", int(sensor_1_value));
//      }
//      if (zone_status_2 == false) {
//        myNextion.setComponentValue("x2", 0.0);
//      }
//      if (zone_status_3 == true) {
//        myNextion.setComponentValue("n0", bpm);
//      }
//      if (zone_status_3 == false) {
//        myNextion.setComponentValue("n0", 0);
//      }
//      if (WiFi.status() == WL_CONNECTED) {
//        myNextion.setComponentText("t0", "Wifi Baglantisi Var");
//        myNextion.setComponentValue("n2", (130 + wifi_strength));
//      }
//      if (WiFi.status() != WL_CONNECTED) {
//        myNextion.setComponentText("t0", "Wifi Baglantisi Yok");
//        myNextion.setComponentValue("n2", 0);
//      }
//      if (heat_status == "heating") {
//        myNextion.setComponentText("t1", "Unite Ici Isitiliyor");
//      }
//      if (heat_status == "cooling") {
//        myNextion.setComponentText("t1", "Unite Ici Sogutuluyor");
//      }
//      if (heat_status == "idle") {
//        myNextion.setComponentText("t1", "Ic Sicaklik Dengede");
//      }
//      if (device_status_2 == "active") {
//        myNextion.setComponentText("t2", "Sicaklik Modu Aktif");
//      }
//      if (device_status_2 == "passive") {
//        myNextion.setComponentText("t2", "Sicaklik Modu Pasif");
//      }
//      if (device_status_4 == "active") {
//        myNextion.setComponentText("t3", "Aydinlatma Aktif");
//      }
//      if (device_status_4 == "passive") {
//        myNextion.setComponentText("t3", "Aydinlatma Pasif");
//      }
//      if (device_status_3 == "active") {
//        myNextion.setComponentText("t4", "Uv Aktif");
//      }
//      if (device_status_3 == "passive") {
//        myNextion.setComponentText("t4", "Uv Pasif");
//      }
//      if (device_status == "active") {
//        myNextion.sendCommand("b12.txt=\"Taburcu Et\"");
//        myNextion.setComponentText("t5", "Yatan Hasta Var");
//      }
//      if (device_status == "passive") {
//        myNextion.sendCommand("b12.txt=\"-\"");
//        myNextion.sendCommand("b13.txt=\"||\"");
//        myNextion.setComponentText("t5", "Yatan Hasta Yok");
//      }
//      if (zone_status_1 == false) {
//        myNextion.sendCommand("b0.txt=\"-\"");
//      }
//      if (zone_status_1 == true) {
//        myNextion.sendCommand("b0.txt=\"Ekg\"");
//      }
//      //myNextion.sendCommand("page page9");
//      //myNextion.setComponentValue("n1_human", sensor_1_value);
//      //myNextion.setComponentText("tidno", deviceid);
//    }
//  }
//}
//
//void nextion_Send_Data_After_Take(String message) {
//  if (message == "&0_b0!" && zone_status_1 == true) {
//    myNextion.sendCommand("page page_ekg");
//    ekg_active_value = 1;
//    relay_6_cloud_value = "0"; // Main Supply
//  }
//  if (message == "&1_b0!") {
//    myNextion.sendCommand("page page_home");
//    ekg_active_value = 0;
//    relay_6_cloud_value = "1"; // Main Supply
//  }
//
//  if (message == "&0_b1!") {
//    if (device_status_2 == "active") {
//      device_status_2 = "passive";
//    }
//    else {
//      device_status_2 = "active";
//    }
//  }
//
//  if (message == "&0_b2!") {
//    if (device_status == "passive") {
//      if (device_status_3 == "active") {
//        device_status_3 = "passive";
//      }
//      else {
//        device_status_3 = "active";
//      }
//    }
//  }
//
//  if (message == "&0_b3!") {
//    if (device_status_4 == "active") {
//      device_status_4 = "passive";
//    }
//    else {
//      device_status_4 = "active";
//    }
//  }
//
//  if (message == "&0_b5!") {
//  }
//
//  if (message == "&0_b10!") {
//    if (entrance_delay_time > 10) {
//      entrance_delay_time = float(entrance_delay_time - 0.5);
//      myNextion.setComponentValue("x3", int(entrance_delay_time * 10));
//    }
//  }
//  if (message == "&0_b11!") {
//    if (entrance_delay_time < 40) {
//      entrance_delay_time = float(entrance_delay_time + 0.5);
//      myNextion.setComponentValue("x3", int(entrance_delay_time * 10));
//    }
//  }
//  if (message == "&0_b12!") {
//    if (device_status == "active") {
//      ademco_id = "R501-000V" + String(version);
//      gsm_ademco_id = "R501-000&gsmV" + String(version);
//      if (wifi_Http_Post_Request_Create_Emergency(true) == 1) {
//        Serial.println("Ademco Send To Server R501-000 Device Passive");
//        last_device_http_counter = device_http_counter;
//        EEPROM.write(107, int(device_http_counter));
//        EEPROM.write(108, int(last_device_http_counter));
//        EEPROM.commit();
//      }
//      ademco_id = "E602-000V" + String(version);
//    }
//  }
//  if (message == "&0_b13!") {
//    if (device_status == "active") {
//      if (pause_counter == 1) {
//        device_status_2 = "passive";
//        myNextion.sendCommand("b13.txt=\">\"");
//      }
//      if (pause_counter == 2) {
//        device_status_2 = "active";
//        pause_counter = 0;
//        myNextion.sendCommand("b13.txt=\"||\"");
//      }
//      pause_counter++;
//      Serial.println(pause_counter);
//    }
//  }
//  if (message == "&0_b6!") {
//    if (device_status == "active") {
//      device_status = "passive";
//      Serial.println("device deactived manually");
//    }
//    else if (device_status == "passive") {
//      device_status = "active";
//      Serial.println("device actived manually");
//    }
//  }
//  if (message == "&0_b4!") {
//    wifi_reset_counter++;
//    if (wifi_reset_counter == 10) {
//      reset_Eeprom();
//      ESP.restart();
//    }
//  }
//}
