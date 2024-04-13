////gsm module settings
//// Gsm saatini Aktif etme
////AT+CCLK?
////AT+CLTS=1
////AT+CLTS?
////AT&W //ayarlatı kaydet gsm' i yeniden başlat
////AT+CCLK?
//
//String apn = "internet";                       //APN
//String apn_u = "";                     //APN-Username
//String apn_p = "";                     //APN-Password
//String gsm_signal_strength;
//int gsm_check_counter = 0;
//int gsm_status = 0;
//int last_gsm_status = 0;
//int gsm_error = 0;
//String gsm_serial_data = "";
//
//unsigned long previousMillis_gsm_post1_timer = 0;
//const long interval_gsm_post1_timer = 100;
//
//unsigned long previousMillis_gsm_get1_timer = 0;
//const long interval_gsm_get1_timer = 100;
//
//unsigned long previousMillis_gsm_check_timer = 0;
//const long interval_gsm_check_timer = 1000;
//
//int gsm_counter = 0;
//int last_gsm_counter = 0;
//
//void gsm_Health_Control() {
//  gsm_Check_Timer();
//  //  Serial.print("gsm_check_counter");
//  //  Serial.print("-");
//  //  Serial.println(gsm_check_counter);
//  // timer 1000 ms ye ayarlı yani 1 dk
//  if (gsm_check_counter > 60 && gsm_counter < 1000) {
//    //sim800l resetle
//    Serial.println("reset sim");
//    gsm_Restart();
//    gsm_check_counter = 0;
//  }
//  if (gsm_serial_data.indexOf("+HTTPACTION:") > 0 && gsm_serial_data.indexOf("601") > 0) {
//    gsm_Restart();
//    Serial.print(gsm_status);
//    Serial.print("-");
//    Serial.println(gsm_error);
//    gsm_error++;
//    gsm_check_counter = 0;
//    gsm_serial_data = "";
//  }
//}
//
//void gsm_Check_Timer() {
//  unsigned long currentMillis = millis();
//  if (currentMillis - previousMillis_gsm_check_timer >= interval_gsm_check_timer) {
//    previousMillis_gsm_check_timer = currentMillis;
//    gsm_check_counter++;
//  }
//}
//
//void gsm_Timer() {
//  unsigned long currentMillis = millis();
//  if (currentMillis - previousMillis_gsm_post1_timer >= interval_gsm_post1_timer) {
//    previousMillis_gsm_post1_timer = currentMillis;
//    gsm_counter++;
//  }
//}
//
//void gsm_Send_Httppost_1(String url) {
//  if (wifi_request_counter > test_signal_time * 2 ) {
//  }
//  if (gsm_counter == 40 && last_gsm_counter != gsm_counter) {
//    last_gsm_counter = gsm_counter;
//    Serial2.println("AT+CLTS=1");
//  }
//  if (gsm_counter == 42 && last_gsm_counter != gsm_counter) {
//    last_gsm_counter = gsm_counter;
//    Serial2.println("AT+CCLK?");
//  }
//  if (gsm_counter == 44 && last_gsm_counter != gsm_counter) {
//    last_gsm_counter = gsm_counter;
//    Serial2.println("AT+SAPBR=3,1,APN," + apn);
//  }
//  if (gsm_counter == 48 && last_gsm_counter != gsm_counter) {
//    last_gsm_counter = gsm_counter;
//    Serial2.println("AT+SAPBR =1,1");
//  }
//  if (gsm_counter == 50 && last_gsm_counter != gsm_counter) {
//    last_gsm_counter = gsm_counter;
//    Serial2.println("AT+HTTPINIT");
//  }
//  if (gsm_counter == 52 && last_gsm_counter != gsm_counter) {
//    last_gsm_counter = gsm_counter;
//    Serial2.println("AT+HTTPPARA=CID,1");
//  }
//  if (gsm_counter == 54 && last_gsm_counter != gsm_counter) {
//    last_gsm_counter = gsm_counter;
//    Serial2.println("AT+HTTPPARA=URL," + url);
//  }
//  if (gsm_counter == 56 && last_gsm_counter != gsm_counter) {
//    last_gsm_counter = gsm_counter;
//    Serial2.println("AT+HTTPSSL=0");// urlsi https olursa = 1, sadece http olursa 0 olacak
//  }
//  //  if (gsm_counter == 57 && last_gsm_counter != gsm_counter) {
//  //    last_gsm_counter = gsm_counter;
//  //    Serial2.println("AT+HTTPPARA=Cookie," + auth_session_id); //session
//  //  }
//  if (gsm_counter == 58 && last_gsm_counter != gsm_counter) {
//    last_gsm_counter = gsm_counter;
//    Serial2.println("AT+HTTPPARA=CONTENT,application/json"); //application/json
//  }
//  if (gsm_counter == 60 && last_gsm_counter != gsm_counter) {
//    last_gsm_counter = gsm_counter;
//    Serial2.println("AT+HTTPDATA=192,10000");
//  }
//  if (gsm_counter == 62 && last_gsm_counter != gsm_counter) {
//    wifi_request_counter++;
//    Serial.print("Gsm Ademco Id: ");
//    Serial.println(gsm_ademco_id);
//    Serial.print("Gsm wifi_request_counter: ");
//    Serial.println(wifi_request_counter);
//
//    if (wifi_request_counter == test_signal_time * 2 ) {
//      create_report = true;
//      wifi_request_counter = 0;
//    }
//    else {
//      create_report = false;
//    }
//    last_gsm_counter = gsm_counter;
//    if (gsm_ademco_id != last_gsm_ademco_id || gsm_ademco_id == "E602-000&gsm") {
//      last_gsm_ademco_id = gsm_ademco_id;
//    }
//    if (gsm_ademco_id != "E602-000&gsm") {
//      create_report = true;
//    }
//    Serial2.println("{\"jsonrpc\":\"2.0\",\"method\":\"create\",\"params\":{\"device_id\":\"" + id + "\",\"code\":\"" + String(gsm_ademco_id) + "\",\"zone\":\"2\",\"create_report\":" + String(create_report) + ",\"device_update\":" + device_update + "},\"id\":569151295}");
//    if (gsm_error == 0) {
//      gsm_ademco_id = "E602-000&gsm";
//    }
//  }
//  if (gsm_counter == 150 && last_gsm_counter != gsm_counter) {
//    last_gsm_counter = gsm_counter;
//    Serial2.println("AT+HTTPACTION=1");
//  }
//  if (gsm_counter == 200 && last_gsm_counter != gsm_counter) {
//    last_gsm_counter = gsm_counter;
//    Serial2.println("AT+HTTPREAD");
//  }
//  if (gsm_counter == 202 && last_gsm_counter != gsm_counter) {
//    last_gsm_counter = gsm_counter;
//    Serial2.println("AT+HTTPTERM");
//    //    if (gsm_error == 0) {
//    //      gsm_status = 0;
//    //      gsm_counter = 51;
//    //      gsm_error = 0;
//    //    }
//  }
//  if (gsm_counter == 222 && last_gsm_counter != gsm_counter) {
//    last_gsm_counter = gsm_counter;
//    Serial2.println("AT+SAPBR=0,1");
//    gsm_status = 0;
//    gsm_counter = 35;
//    gsm_error = 0;
//  }
//}
//
////void gsm_Send_Httpget_1(String url) {
////
////  if (gsm_counter == 224 && last_gsm_counter != gsm_counter) {
////    last_gsm_counter = gsm_counter;
////    Serial2.println("AT+CSQ");
////  }
////  if (gsm_counter == 226 && last_gsm_counter != gsm_counter) {
////    last_gsm_counter = gsm_counter;
////    Serial2.println("AT+SAPBR=3,1,APN," + apn);
////  }
////  if (gsm_counter == 228 && last_gsm_counter != gsm_counter) {
////    last_gsm_counter = gsm_counter;
////    Serial2.println("AT+SAPBR =1,1");
////  }
////  if (gsm_counter == 230 && last_gsm_counter != gsm_counter) {
////    last_gsm_counter = gsm_counter;
////    Serial2.println("AT+HTTPINIT");
////  }
////  if (gsm_counter == 232 && last_gsm_counter != gsm_counter) {
////    last_gsm_counter = gsm_counter;
////    Serial2.println("AT+HTTPPARA=CID,1");
////  }
////  if (gsm_counter == 234 && last_gsm_counter != gsm_counter) {
////    last_gsm_counter = gsm_counter;
////    Serial2.println("AT+HTTPPARA=URL," + url);
////  }
////  if (gsm_counter == 236 && last_gsm_counter != gsm_counter) {
////    last_gsm_counter = gsm_counter;
////    Serial2.println("AT+HTTPSSL=0");// urlsi https olursa = 0, sadece http olursa 1 olacak
////  }
////  if (gsm_counter == 238 && last_gsm_counter != gsm_counter) {
////    last_gsm_counter = gsm_counter;
////    Serial2.println("AT+HTTPACTION=0");
////  }
////  if (gsm_counter == 342 && last_gsm_counter != gsm_counter) {
////    last_gsm_counter = gsm_counter;
////    Serial2.println("AT+HTTPREAD");
////  }
////  if (gsm_counter == 352 && last_gsm_counter != gsm_counter) {
////    last_gsm_counter = gsm_counter;
////    Serial2.println("AT+HTTPTERM");
////  }
////  if (gsm_counter == 354 && last_gsm_counter != gsm_counter) {
////    last_gsm_counter = gsm_counter;
////    Serial2.println("AT+SAPBR=0,1");
////    gsm_counter = 0;
////    gsm_status = 0;
////    gsm_error = 0;
////  }
////}
//
//
////Print GSM Status
//void read_Gsm_Serial() {
//  while (Serial2.available()) {
//    gsm_serial_data = Serial2.readString();
//    yield();
//    Serial.println("gsm data:" + gsm_serial_data);
//    gsm_time_picker();
//    gsm_Status_Counter();
//    gsm_Get_Data_Parser();
//  }
//}
//
//void write_Gsm_Serial() {
//  while (Serial.available() > 0) {
//    Serial2.write(Serial.read());
//    yield();
//  }
//}
////Gsm Check and OK - ERROR datas counter
//void gsm_Status_Counter() {
//  if (gsm_serial_data.indexOf("OK") > 0) {
//    gsm_status++;
//    gsm_check_counter = 0;
//    Serial.print(gsm_status);
//    Serial.print("-");
//    Serial.println(gsm_error);
//  }
//  if (gsm_serial_data.indexOf("ERROR") > 0 ) {
//    Serial.print(gsm_status);
//    Serial.print("-");
//    Serial.println(gsm_error);
//    gsm_error++;
//    gsm_check_counter = 0;
//  }
//}
//
//void gsm_Get_Data_Parser() {
//  if (gsm_serial_data.indexOf("+HTTPREAD:") > 0 && gsm_serial_data.indexOf("200") > 0 && gsm_serial_data.indexOf("code") > 0) {
//    device_update = 1;
//  }
//  if (gsm_serial_data.indexOf("+HTTPREAD:") > 0 && gsm_serial_data.indexOf("device_update") > 0) {
//    if ((gsm_serial_data.substring(gsm_serial_data.indexOf("device_update") + 16 , gsm_serial_data.indexOf(", \"device_status"))) == "true") {
//      device_update = 1;
//    }
//    else {
//      device_update = 2;
//    }
//    device_status = (gsm_serial_data.substring(gsm_serial_data.indexOf("device_status") + 17 , gsm_serial_data.indexOf(", \"entrance_delay_time") - 1));
//    entrance_delay_time = (gsm_serial_data.substring(gsm_serial_data.indexOf("entrance_delay_time") + 21 , gsm_serial_data.indexOf(", \"exit_delay_time"))).toInt();
//    exit_delay_time = (gsm_serial_data.substring(gsm_serial_data.indexOf("exit_delay_time") + 18 , gsm_serial_data.indexOf(", \"alarm_time"))).toInt();
//    alarm_time = (gsm_serial_data.substring(gsm_serial_data.indexOf("alarm_time") + 13 , gsm_serial_data.indexOf(", \"default_settings_1"))).toInt();
//
//    if ((gsm_serial_data.substring(gsm_serial_data.indexOf("default_settings_1") + 21 , gsm_serial_data.indexOf(", \"zone_status_1"))) == "true") {
//      default_settings_1 = true;
//    }
//    else {
//      default_settings_1 = false;
//    }
//    if ((gsm_serial_data.substring(gsm_serial_data.indexOf("zone_status_1") + 16 , gsm_serial_data.indexOf(", \"always_on_1"))) == "true") {
//      zone_status_1 = true;
//    }
//    else {
//      zone_status_1 = false;
//    }
//    if ((gsm_serial_data.substring(gsm_serial_data.indexOf("always_on_1") + 14 , gsm_serial_data.indexOf(", \"sudden_alarm_1"))) == "true") {
//      always_on_1 = true;
//    }
//    else {
//      always_on_1 = false;
//    }
//    if ((gsm_serial_data.substring(gsm_serial_data.indexOf("sudden_alarm_1") + 17 , gsm_serial_data.indexOf(", \"default_settings_2"))) == "true") {
//      sudden_alarm_1 = true;
//    }
//    else {
//      sudden_alarm_1 = false;
//    }
//
//    if ((gsm_serial_data.substring(gsm_serial_data.indexOf("default_settings_2") + 21 , gsm_serial_data.indexOf(", \"zone_status_2"))) == "true") {
//      default_settings_2 = true;
//    }
//    else {
//      default_settings_2 = false;
//    }
//    if ((gsm_serial_data.substring(gsm_serial_data.indexOf("zone_status_2") + 16 , gsm_serial_data.indexOf(", \"always_on_2"))) == "true") {
//      zone_status_2 = true;
//    }
//    else {
//      zone_status_2 = false;
//    }
//    if ((gsm_serial_data.substring(gsm_serial_data.indexOf("always_on_2") + 14 , gsm_serial_data.indexOf(", \"sudden_alarm_2"))) == "true") {
//      always_on_2 = true;
//    }
//    else {
//      always_on_2 = false;
//    }
//    if ((gsm_serial_data.substring(gsm_serial_data.indexOf("sudden_alarm_2") + 17 , gsm_serial_data.indexOf(", \"default_settings_3"))) == "true") {
//      sudden_alarm_2 = true;
//    }
//    else {
//      sudden_alarm_2 = false;
//    }
//
//    if ((gsm_serial_data.substring(gsm_serial_data.indexOf("default_settings_3") + 21 , gsm_serial_data.indexOf(", \"zone_status_3"))) == "true") {
//      default_settings_3 = true;
//    }
//    else {
//      default_settings_3 = false;
//    }
//    if ((gsm_serial_data.substring(gsm_serial_data.indexOf("zone_status_3") + 16 , gsm_serial_data.indexOf(", \"always_on_3"))) == "true") {
//      zone_status_3 = true;
//    }
//    else {
//      zone_status_3 = false;
//    }
//    if ((gsm_serial_data.substring(gsm_serial_data.indexOf("always_on_3") + 14 , gsm_serial_data.indexOf(", \"sudden_alarm_3"))) == "true") {
//      always_on_3 = true;
//    }
//    else {
//      always_on_3 = false;
//    }
//    if ((gsm_serial_data.substring(gsm_serial_data.indexOf("sudden_alarm_3") + 17 , gsm_serial_data.indexOf(", \"default_settings_4"))) == "true") {
//      sudden_alarm_3 = true;
//    }
//    else {
//      sudden_alarm_3 = false;
//    }
//
//    if ((gsm_serial_data.substring(gsm_serial_data.indexOf("default_settings_4") + 21 , gsm_serial_data.indexOf(", \"zone_status_4"))) == "true") {
//      default_settings_4 = true;
//    }
//    else {
//      default_settings_4 = false;
//    }
//    if ((gsm_serial_data.substring(gsm_serial_data.indexOf("zone_status_4") + 16 , gsm_serial_data.indexOf(", \"always_on_4"))) == "true") {
//      zone_status_4 = true;
//    }
//    else {
//      zone_status_4 = false;
//    }
//    if ((gsm_serial_data.substring(gsm_serial_data.indexOf("always_on_4") + 14 , gsm_serial_data.indexOf(", \"sudden_alarm_4"))) == "true") {
//      always_on_4 = true;
//    }
//    else {
//      always_on_4 = false;
//    }
//    if ((gsm_serial_data.substring(gsm_serial_data.indexOf("sudden_alarm_4") + 17 , gsm_serial_data.indexOf(", \"wifi_name"))) == "true") {
//      sudden_alarm_4 = true;
//    }
//    else {
//      sudden_alarm_4 = false;
//    }
//    wifi_name = gsm_serial_data.substring(gsm_serial_data.indexOf("wifi_name") + 13 , gsm_serial_data.indexOf(", \"wifi_password") - 1);
//    wifi_password = gsm_serial_data.substring(gsm_serial_data.indexOf("wifi_password") + 17 , gsm_serial_data.indexOf(", \"test_signal_time") - 1);
//
//    test_signal_time = (gsm_serial_data.substring(gsm_serial_data.indexOf("test_signal_time") + 19 , gsm_serial_data.indexOf(", \"last_value"))).toInt();
//
//    String old_wifiname = "";
//    String old_wifipassword = "";
//
//    write_Int_ToEeprom();
//
//    if (wifi_name != ssid || wifi_password != password) {
//      writeStringToEeprom(1, "chwifi" + wifi_name + "-" + wifi_password + "%");
//      Serial.println("Wifi Name and Password Was Changed Over Gsm");
//      delay(5);
//      ESP.restart();
//    }
//
//    device_update = 2;
//
//    Serial.print("device_update:");
//    Serial.println(device_update);
//    Serial.print("device_status:");
//    Serial.println(device_status);
//    Serial.print("entrance_delay_time:");
//    Serial.println(entrance_delay_time);
//    Serial.print("exit_delay_time:");
//    Serial.println(exit_delay_time);
//    Serial.print("alarm_time:");
//    Serial.println(alarm_time);
//    Serial.print("default_settings_1:");
//    Serial.println(default_settings_1);
//    Serial.print("zone_status_1:");
//    Serial.println(zone_status_1);
//    Serial.print("always_on_1:");
//    Serial.println(always_on_1);
//    Serial.print("sudden_alarm_1:");
//    Serial.println(sudden_alarm_1);
//    Serial.print("default_settings_2:");
//    Serial.println(default_settings_2);
//    Serial.print("zone_status_2:");
//    Serial.println(zone_status_2);
//    Serial.print("always_on_2:");
//    Serial.println(always_on_2);
//    Serial.print("sudden_alarm_2:");
//    Serial.println(sudden_alarm_2);
//    Serial.print("default_settings_3:");
//    Serial.println(default_settings_3);
//    Serial.print("zone_status_3:");
//    Serial.println(zone_status_3);
//    Serial.print("always_on_3:");
//    Serial.println(always_on_3);
//    Serial.print("sudden_alarm_3:");
//    Serial.println(sudden_alarm_3);
//    Serial.print("default_settings_4:");
//    Serial.println(default_settings_4);
//    Serial.print("zone_status_4:");
//    Serial.println(zone_status_4);
//    Serial.print("always_on_4:");
//    Serial.println(always_on_4);
//    Serial.print("sudden_alarm_4:");
//    Serial.println(sudden_alarm_4);
//    Serial.print("wifi_name:");
//    Serial.println(wifi_name);
//    Serial.print("wifi_password:");
//    Serial.println(wifi_password);
//    Serial.print("test_signal_time:");
//    Serial.println(test_signal_time);
//  }
//}
//
//void gsm_time_picker() {
//  if (gsm_serial_data.indexOf("+CCLK:") > 0 ) {
//    String allyear = (gsm_serial_data.substring(gsm_serial_data.indexOf("+CCLK:") + 8 , gsm_serial_data.indexOf("+CCLK:") + 25));
//    String year = (gsm_serial_data.substring(gsm_serial_data.indexOf("+CCLK:") + 8 , gsm_serial_data.indexOf("+CCLK:") + 10));
//    te.Year = atoi (year.c_str ());
//    String month = (gsm_serial_data.substring(gsm_serial_data.indexOf("+CCLK:") + 11 , gsm_serial_data.indexOf("+CCLK:") + 13));
//    te.Month = atoi (month.c_str ());
//    String day = (gsm_serial_data.substring(gsm_serial_data.indexOf("+CCLK:") + 14 , gsm_serial_data.indexOf("+CCLK:") + 16));
//    te.Day = atoi (day.c_str ());
//    String hour = (gsm_serial_data.substring(gsm_serial_data.indexOf("+CCLK:") + 17 , gsm_serial_data.indexOf("+CCLK:") + 19));
//    te.Hour = atoi (hour.c_str ());
//    String minute = (gsm_serial_data.substring(gsm_serial_data.indexOf("+CCLK:") + 20 , gsm_serial_data.indexOf("+CCLK:") + 22));
//    te.Minute = atoi (minute.c_str ());
//    String second = (gsm_serial_data.substring(gsm_serial_data.indexOf("+CCLK:") + 23 , gsm_serial_data.indexOf("+CCLK:") + 25));
//    te.Second = atoi (second.c_str ());
//    unixTime =  makeTime(te) + 946760400;
//    timestamp = String(unixTime);
//    Serial.print("time=");
//    Serial.println(timestamp);
//  }
//}
//
//String json_Object_Creator()
//{
//  //  StaticJsonBuffer<3400> JSONbuffer;
//  //  JsonObject& JsonData = JSONbuffer.createObject();
//  //  JsonData["sensors"] = all_sensor_data;
//  //  JsonData["time"] = String(unixTime);
//  //  String requestData;
//  //  JsonData.printTo(requestData);
//  //  //Serial.println(requestData);
//  //  return requestData;
//}
