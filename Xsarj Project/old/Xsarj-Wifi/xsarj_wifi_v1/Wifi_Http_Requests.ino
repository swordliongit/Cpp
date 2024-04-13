//Json To String Coverter Link: https://jsontostring.com/

unsigned long previousMillis_wifi_request_timer = 0;
const long interval_wifi_request_timer = 15000;


//void wifi_Http_Post_Request_Create() {
//  unsigned long currentMillis = millis();
//  if (currentMillis - previousMillis_wifi_request_timer >= interval_wifi_request_timer) {
//    previousMillis_wifi_request_timer = currentMillis;
//    if (WiFi.status() == WL_CONNECTED) {
//      HTTPClient http;
//      http.begin(server_url + "/create/report-for-device");
//      http.addHeader("Cookie", auth_session_id);
//      http.addHeader("Content-Type", "application/json");
//      http.addHeader("Connection", "keep-alive");
//      http.addHeader("Accept-Encoding", "gzip, deflate, br");
//      http.addHeader("Accept", "*/*");
//      http.addHeader("User-Agent", "PostmanRuntime/7.26.8");
//      if (wifi_request_counter == test_signal_time * 4 ) {
//        create_report = true;
//        wifi_request_counter = 0;
//      }
//      else {
//        create_report = false;
//      }
//      if (wifi_request_counter > test_signal_time * 4 ) {
//        wifi_request_counter = 0;
//      }
//      if (ademco_id.indexOf("E130") >= 0) {
//        create_report = false;
//      }
//      http.setConnectTimeout(5000);
//      int httpResponseCode = http.POST("{\"jsonrpc\":\"2.0\",\"method\":\"create\",\"params\":{\"device_id\":\"" + id + "\",\"code\":\"" + String(ademco_id) + "\",\"zone\":\"2\",\"create_report\":" + String(create_report) + ",\"device_update\":" + device_update + "},\"id\":569151295}");
//      if (httpResponseCode > 0) {
//        String response = http.getString();
//        Serial.println(httpResponseCode);
//        Serial.println(response);
//        if (httpResponseCode == 200 && response.indexOf("\"error\":") < 0) {
//          wifi_request_counter++;
//        }
//        Serial.println("wifi_request_counter: " + String(wifi_request_counter));
//        wifi_Get_Data_Parser(response);
//      } else {
//        Serial.print("Error on sending Post Create Request: ");
//        Serial.println(httpResponseCode);
//      }
//      http.end();
//    } else {
//      Serial.println("Error in WiFi connection(Http Post Ask Server)");
//    }
//  }
//}

void wifi_Http_Post_Request_Create_Setup(boolean report_status) {
  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;
    http.begin(server_url + "/create/report-for-device");
    http.addHeader("Cookie", auth_session_id);
    http.addHeader("Content-Type", "application/json");
    http.addHeader("Connection", "keep-alive");
    http.addHeader("Accept-Encoding", "gzip, deflate, br");
    http.addHeader("Accept", "*/*");
    http.addHeader("User-Agent", "PostmanRuntime/7.26.8");
    ademco_id = "E602-000V" + String(version);
    http.setConnectTimeout(5000);
    int httpResponseCode = http.POST("{\"jsonrpc\":\"2.0\",\"method\":\"create\",\"params\":{\"device_id\":\"" + id + "\",\"code\":\"" + String(ademco_id) + "\",\"zone\":\"2\",\"create_report\":" + String(report_status) + ",\"device_update\":" + device_update + "},\"id\":569151295}");

    if (httpResponseCode > 0) {
      String response = http.getString();
      Serial.println(httpResponseCode);
      Serial.println(response);
      Serial.println("Device Started Http Request!");
      wifi_Get_Data_Parser(response);
    } else {
      Serial.print("Error on sending Post Create Request Setup: ");
      Serial.println(httpResponseCode);
    }
    http.end();
  } else {
    Serial.println("Error in WiFi connection (Http Post Ask Server Setup)");
  }
}


int wifi_Http_Post_Request_Create_Emergency(boolean report_status) {
  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;
    http.begin(server_url + "/create/report-for-device");
    http.addHeader("Cookie", auth_session_id);
    http.addHeader("Content-Type", "application/json");
    http.addHeader("Connection", "keep-alive");
    http.addHeader("Accept-Encoding", "gzip, deflate, br");
    http.addHeader("Accept", "*/*");
    http.addHeader("User-Agent", "PostmanRuntime/7.26.8");
    http.setConnectTimeout(5000);
    int httpResponseCode = http.POST("{\"jsonrpc\":\"2.0\",\"method\":\"create\",\"params\":{\"device_id\":\"" + id + "\",\"code\":\"" + String(ademco_id) + "\",\"zone\":\"2\",\"create_report\":" + String(report_status) + ",\"device_update\":" + device_update + "},\"id\":569151295}");

    if (httpResponseCode > 0) {
      String response = http.getString();
      Serial.println(httpResponseCode);
      Serial.println(response);
      Serial.println("emergenct http request started");
      wifi_Get_Data_Parser(response);
    } else {
      Serial.print("Error on sending Post Create Request Emergency: ");
      Serial.println(httpResponseCode);
    }
    if (httpResponseCode == 200) {
      return 1;
    }
    else {
      return 0;
    }
    http.end();
  } else {
    Serial.println("Error in WiFi connection (Http Post Ask Server Emergency)");
  }
}


void wifi_Get_Data_Parser(String response) {
  if (response.indexOf("200") > 0 && response.indexOf("code") > 0 && response.indexOf("400 Bad") < 0 && response.indexOf("W3C") < 0 && response.indexOf("Error") < 0 && response.indexOf("exception") < 0) {
    device_update = 1;
  }
  if (response.indexOf("device_update") > 0 && response.indexOf("200") > 0 && response.indexOf("code") > 0 && response.indexOf("wifi_name") >= 0 && response.indexOf("wifi_password") >= 0 && response.indexOf("last_value") >= 0 && response.indexOf("Error") < 0 && response.indexOf("exception") < 0) {
    if ((response.substring(response.indexOf("device_update") + 16 , response.indexOf(", \"device_status"))) == "true") {
      device_update = 1;
    }
    else {
      device_update = 2;
    }
    device_status = (response.substring(response.indexOf("device_status") + 17 , response.indexOf(", \"device_status_1") - 1));
    device_status_1 = (response.substring(response.indexOf("device_status_1") + 19 , response.indexOf(", \"device_status_2") - 1));
    device_status_2 = (response.substring(response.indexOf("device_status_2") + 19 , response.indexOf(", \"device_status_3") - 1));
    device_status_3 = (response.substring(response.indexOf("device_status_3") + 19 , response.indexOf(", \"device_status_4") - 1));
    device_status_4 = (response.substring(response.indexOf("device_status_4") + 19 , response.indexOf(", \"device_status_5") - 1));
    device_status_5 = (response.substring(response.indexOf("device_status_5") + 19 , response.indexOf(", \"device_status_6") - 1));
    device_status_6 = (response.substring(response.indexOf("device_status_6") + 19 , response.indexOf(", \"device_status_7") - 1));
    device_status_7 = (response.substring(response.indexOf("device_status_7") + 19 , response.indexOf(", \"device_status_8") - 1));
    device_status_8 = (response.substring(response.indexOf("device_status_8") + 19 , response.indexOf(", \"device_status_9") - 1));
    device_status_9 = (response.substring(response.indexOf("device_status_9") + 19 , response.indexOf(", \"device_status_10") - 1));
    device_status_10 = (response.substring(response.indexOf("device_status_10") + 20 , response.indexOf(", \"device_status_11") - 1));
    device_status_11 = (response.substring(response.indexOf("device_status_11") + 20 , response.indexOf(", \"device_status_12") - 1));
    device_status_12 = (response.substring(response.indexOf("device_status_12") + 20 , response.indexOf(", \"device_status_13") - 1));
    device_status_13 = (response.substring(response.indexOf("device_status_13") + 20 , response.indexOf(", \"device_status_14") - 1));
    device_status_14 = (response.substring(response.indexOf("device_status_14") + 20 , response.indexOf(", \"device_status_15") - 1));
    device_status_15 = (response.substring(response.indexOf("device_status_15") + 20 , response.indexOf(", \"device_status_16") - 1));
    device_status_16 = (response.substring(response.indexOf("device_status_16") + 20 , response.indexOf(", \"setting_1_value") - 1));

    setting_1_value = (response.substring(response.indexOf("setting_1_value") + 18 , response.indexOf(", \"setting_2_value"))).toInt();
    setting_2_value = (response.substring(response.indexOf("setting_2_value") + 18 , response.indexOf(", \"setting_3_value"))).toInt();
    setting_3_value = (response.substring(response.indexOf("setting_3_value") + 18 , response.indexOf(", \"setting_4_valuev"))).toInt();
    setting_4_value = (response.substring(response.indexOf("setting_4_value") + 18 , response.indexOf(", \"setting_5_value"))).toInt();
    setting_5_value = (response.substring(response.indexOf("setting_5_value") + 18 , response.indexOf(", \"setting_6_value"))).toInt();
    setting_6_value = (response.substring(response.indexOf("setting_6_value") + 18 , response.indexOf(", \"setting_7_value"))).toInt();
    setting_7_value = (response.substring(response.indexOf("setting_7_value") + 18 , response.indexOf(", \"setting_8_value"))).toInt();
    setting_8_value = (response.substring(response.indexOf("setting_8_value") + 18 , response.indexOf(", \"setting_9_value"))).toInt();
    setting_9_value = (response.substring(response.indexOf("setting_9_value") + 18 , response.indexOf(", \"setting_10_value"))).toInt();
    setting_10_value = (response.substring(response.indexOf("setting_10_value") + 19 , response.indexOf(", \"entrance_delay_time"))).toInt();
    entrance_delay_time = (response.substring(response.indexOf("entrance_delay_time") + 21 , response.indexOf(", \"exit_delay_time"))).toFloat();
    exit_delay_time = (response.substring(response.indexOf("exit_delay_time") + 18 , response.indexOf(", \"alarm_time"))).toFloat();
    alarm_time = (response.substring(response.indexOf("alarm_time") + 13 , response.indexOf(", \"default_settings_1"))).toFloat();

    if ((response.substring(response.indexOf("default_settings_1") + 21 , response.indexOf(", \"zone_status_1"))) == "true") {
      default_settings_1 = true;
    }
    else {
      default_settings_1 = false;
    }
    if ((response.substring(response.indexOf("zone_status_1") + 16 , response.indexOf(", \"always_on_1"))) == "true") {
      zone_status_1 = true;
    }
    else {
      zone_status_1 = false;
    }
    if ((response.substring(response.indexOf("always_on_1") + 14 , response.indexOf(", \"sudden_alarm_1"))) == "true") {
      always_on_1 = true;
    }
    else {
      always_on_1 = false;
    }
    if ((response.substring(response.indexOf("sudden_alarm_1") + 17 , response.indexOf(", \"default_settings_2"))) == "true") {
      sudden_alarm_1 = true;
    }
    else {
      sudden_alarm_1 = false;
    }

    if ((response.substring(response.indexOf("default_settings_2") + 21 , response.indexOf(", \"zone_status_2"))) == "true") {
      default_settings_2 = true;
    }
    else {
      default_settings_2 = false;
    }
    if ((response.substring(response.indexOf("zone_status_2") + 16 , response.indexOf(", \"always_on_2"))) == "true") {
      zone_status_2 = true;
    }
    else {
      zone_status_2 = false;
    }
    if ((response.substring(response.indexOf("always_on_2") + 14 , response.indexOf(", \"sudden_alarm_2"))) == "true") {
      always_on_2 = true;
    }
    else {
      always_on_2 = false;
    }
    if ((response.substring(response.indexOf("sudden_alarm_2") + 17 , response.indexOf(", \"default_settings_3"))) == "true") {
      sudden_alarm_2 = true;
    }
    else {
      sudden_alarm_2 = false;
    }

    if ((response.substring(response.indexOf("default_settings_3") + 21 , response.indexOf(", \"zone_status_3"))) == "true") {
      default_settings_3 = true;
    }
    else {
      default_settings_3 = false;
    }
    if ((response.substring(response.indexOf("zone_status_3") + 16 , response.indexOf(", \"always_on_3"))) == "true") {
      zone_status_3 = true;
    }
    else {
      zone_status_3 = false;
    }
    if ((response.substring(response.indexOf("always_on_3") + 14 , response.indexOf(", \"sudden_alarm_3"))) == "true") {
      always_on_3 = true;
    }
    else {
      always_on_3 = false;
    }
    if ((response.substring(response.indexOf("sudden_alarm_3") + 17 , response.indexOf(", \"default_settings_4"))) == "true") {
      sudden_alarm_3 = true;
    }
    else {
      sudden_alarm_3 = false;
    }

    if ((response.substring(response.indexOf("default_settings_4") + 21 , response.indexOf(", \"zone_status_4"))) == "true") {
      default_settings_4 = true;
    }
    else {
      default_settings_4 = false;
    }
    if ((response.substring(response.indexOf("zone_status_4") + 16 , response.indexOf(", \"always_on_4"))) == "true") {
      zone_status_4 = true;
    }
    else {
      zone_status_4 = false;
    }
    if ((response.substring(response.indexOf("always_on_4") + 14 , response.indexOf(", \"sudden_alarm_4"))) == "true") {
      always_on_4 = true;
    }
    else {
      always_on_4 = false;
    }
    if ((response.substring(response.indexOf("sudden_alarm_4") + 17 , response.indexOf(", \"wifi_name"))) == "true") {
      sudden_alarm_4 = true;
    }
    else {
      sudden_alarm_4 = false;
    }
    wifi_name = response.substring(response.indexOf("wifi_name") + 13 , response.indexOf(", \"wifi_password") - 1);
    wifi_password = response.substring(response.indexOf("wifi_password") + 17 , response.indexOf(", \"test_signal_time") - 1);

    test_signal_time = (response.substring(response.indexOf("test_signal_time") + 19 , response.indexOf(", \"last_value"))).toInt();

    String old_wifiname = "";
    String old_wifipassword = "";

    if (wifi_name != ssid || wifi_password != password) {
      writeStringToEeprom(1, "w_" + wifi_name + "-" + wifi_password + "%" + String(entrance_delay_time) + "#" + String(exit_delay_time) + "!");
      Serial.println("Wifi Name and Password Was Changed Over Wifi");
      delay(5);
      ESP.restart();
    }

    if (wifi_name == ssid || wifi_password == password) {
      writeStringToEeprom(1, "w_" + wifi_name + "-" + wifi_password + "%" + String(entrance_delay_time) + "#" + String(exit_delay_time) + "!");
      Serial.println("Wifi Name and Password Was Changed Over Wifi");
    }

    device_update = 2;
    Serial.println("---------------- Data Get And Parsed By Wifi -----------------");
    Serial.print("device_update:");
    Serial.println(device_update);
    Serial.print("device_status:");
    Serial.println(device_status);
    Serial.print("device_status_1:");
    Serial.println(device_status_1);
    Serial.print("device_status_2:");
    Serial.println(device_status_2);
    Serial.print("device_status_3:");
    Serial.println(device_status_3);
    Serial.print("device_status_4:");
    Serial.println(device_status_4);
    Serial.print("device_status_5:");
    Serial.println(device_status_5);
    Serial.print("device_status_6:");
    Serial.println(device_status_6);
    Serial.print("device_status_7:");
    Serial.println(device_status_7);
    Serial.print("device_status_8:");
    Serial.println(device_status_8);
    Serial.print("device_status_9:");
    Serial.println(device_status_9);
    Serial.print("device_status_10:");
    Serial.println(device_status_10);
    Serial.print("device_status_11:");
    Serial.println(device_status_11);
    Serial.print("device_status_12:");
    Serial.println(device_status_12);
    Serial.print("device_status_13:");
    Serial.println(device_status_13);
    Serial.print("device_status_14:");
    Serial.println(device_status_14);
    Serial.print("device_status_15:");
    Serial.println(device_status_15);
    Serial.print("device_status_16:");
    Serial.println(device_status_16);
    Serial.print("setting_1_value:");
    Serial.println(setting_1_value);
    Serial.print("setting_2_value:");
    Serial.println(setting_2_value);
    Serial.print("setting_3_value:");
    Serial.println(setting_3_value);
    Serial.print("setting_4_value:");
    Serial.println(setting_4_value);
    Serial.print("setting_5_value:");
    Serial.println(setting_5_value);
    Serial.print("setting_6_value:");
    Serial.println(setting_6_value);
    Serial.print("setting_7_value:");
    Serial.println(setting_7_value);
    Serial.print("setting_8_value:");
    Serial.println(setting_8_value);
    Serial.print("setting_9_value:");
    Serial.println(setting_9_value);
    Serial.print("setting_10_value:");
    Serial.println(setting_10_value);
    Serial.print("entrance_delay_time:");
    Serial.println(entrance_delay_time);
    Serial.print("exit_delay_time:");
    Serial.println(exit_delay_time);
    Serial.print("alarm_time:");
    Serial.println(alarm_time);
    Serial.print("default_settings_1:");
    Serial.println(default_settings_1);
    Serial.print("zone_status_1:");
    Serial.println(zone_status_1);
    Serial.print("always_on_1:");
    Serial.println(always_on_1);
    Serial.print("sudden_alarm_1:");
    Serial.println(sudden_alarm_1);
    Serial.print("default_settings_2:");
    Serial.println(default_settings_2);
    Serial.print("zone_status_2:");
    Serial.println(zone_status_2);
    Serial.print("always_on_2:");
    Serial.println(always_on_2);
    Serial.print("sudden_alarm_2:");
    Serial.println(sudden_alarm_2);
    Serial.print("default_settings_3:");
    Serial.println(default_settings_3);
    Serial.print("zone_status_3:");
    Serial.println(zone_status_3);
    Serial.print("always_on_3:");
    Serial.println(always_on_3);
    Serial.print("sudden_alarm_3:");
    Serial.println(sudden_alarm_3);
    Serial.print("default_settings_4:");
    Serial.println(default_settings_4);
    Serial.print("zone_status_4:");
    Serial.println(zone_status_4);
    Serial.print("always_on_4:");
    Serial.println(always_on_4);
    Serial.print("sudden_alarm_4:");
    Serial.println(sudden_alarm_4);
    Serial.print("wifi_name:");
    Serial.println(wifi_name);
    Serial.print("wifi_password:");
    Serial.println(wifi_password);
    Serial.print("test_signal_time:");
    Serial.println(test_signal_time);

    write_Int_ToEeprom();
  }
}
