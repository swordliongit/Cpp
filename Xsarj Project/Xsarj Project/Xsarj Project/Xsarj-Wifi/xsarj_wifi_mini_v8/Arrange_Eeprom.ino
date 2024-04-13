//void change_wifi_Command() {
//  if (data_from_ble.startsWith("w_")) {
//    String data = data_from_ble;
//    Serial.println("here1");
//    writeStringToEeprom(1, data);
//    arrangeWifiAndPassword();
//    if (data.startsWith("w_")) {
//      delay(5);
//      ESP.restart();
//    }
//  }
//}

void arrangeWifiAndPassword() {
  String recivedData;
  recivedData = read_StringFromEeprom(1);
  Serial.print("Read Wifi Data:");
  Serial.println(recivedData);
  if (recivedData.startsWith("w_")) {
    wifiname = (recivedData.substring(recivedData.indexOf("w_") + 2, recivedData.indexOf("-")));
    wifipassword = (recivedData.substring(recivedData.indexOf("-") + 1, recivedData.indexOf("%")));
    entrance_delay_time = (recivedData.substring(recivedData.indexOf("%") + 1, recivedData.indexOf("#"))).toFloat();
    exit_delay_time = (recivedData.substring(recivedData.indexOf("#") + 1, recivedData.indexOf("!"))).toFloat();
    delay(1000);
    swSer.println("Master Starting");
    delay(1000);
    swSer.println("w_" + String(wifiname) + "-" + String(wifipassword) + "%");
    Serial.println("---------- Master Send To Led Panel Wifi Data ----------------");
    Serial.print("entrance_delay_time:");
    Serial.println(entrance_delay_time);
    Serial.print("exit_delay_time:");
    Serial.println(exit_delay_time);
    wifiname.toCharArray(ssid, 50);
    wifipassword.toCharArray(password, 50);
    yield();
  }
}

void change_Config_Command() {
  if (second_esp_serial_data.indexOf("c1-") == 0 && second_esp_serial_data.indexOf("?") > 0 && second_esp_serial_data.length() > 0) {
    String data = second_esp_serial_data;
    write_Int_ToEeprom();
    read_Int_Eeprom();
  }
}


void reset_Wifi_Name() {
  reset_button_esp_value = digitalRead(reset_button_esp);
  if (reset_button_esp_value == 0) {
    reset_Eeprom();
  }
}

void tryToReconnectWifi_Setup() {
  if (WiFi.status() != WL_CONNECTED) {
    Serial.println("Wifi Name Found Succesfully. Trying To Connect..");
    WiFi.disconnect();
    WiFi.mode(WIFI_OFF);
    WiFi.mode(WIFI_STA);
    WiFi.begin(ssid, password);
    delay(500);
    Serial.print(".");
    if (WiFi.waitForConnectResult() != WL_CONNECTED) {
      Serial.printf("WiFi Failed!\n");
      ESP.restart();
      return;
    }
    WiFi.setSleep(false);
  }
  if (WiFi.status() == WL_CONNECTED) {
    wifi_strength = WiFi.RSSI();
    wifi_connected_counter++;
    wifi_status = 1;
  }
}


void tryToReconnectWifi() {
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis_wifi_timer >= interval_wifi_timer) {
    previousMillis_wifi_timer = currentMillis;
    unsigned long currentMillis = millis();
    if (WiFi.status() != WL_CONNECTED) {
      Serial.println("Wifi Name Found Succesfully. Trying To Connect..");
      WiFi.disconnect();
      WiFi.mode(WIFI_OFF);
      WiFi.mode(WIFI_STA);
      WiFi.begin(ssid, password);
      //    if (WiFi.waitForConnectResult() != WL_CONNECTED) {
      //      Serial.printf("WiFi Failed!\n");
      //      return;
      //    }
      WiFi.setSleep(false);
    }
    if (wifi_connected_counter == 0 && WiFi.status() == WL_CONNECTED) {
      ESP.restart();
    }
  }
}


void writeStringToEeprom(char add, String data)
{
  int _size = data.length();
  int i;
  for (i = 0; i < _size; i++)
  {
    EEPROM.write(add + i, data[i]);
  }
  EEPROM.write(add + _size, '\0'); //Add termination null character for String Data
  EEPROM.commit();
}

String read_StringFromEeprom(char add)
{
  int i;
  char data[100]; //Max 100 Bytes
  int len = 0;
  unsigned char k;
  k = EEPROM.read(add);
  while (k != '\0' && len < 59) //Read until null character
  {
    k = EEPROM.read(add + len);
    data[len] = k;
    len++;
  }
  data[len] = '\0';
  return String(data);
}

void reset_Eeprom() {
  Serial.println("WiFi Eeprom Resetted!");
  writeStringToEeprom(1, "nodata");
  ESP.restart();
}

void testEepromWorking() {
  if (!EEPROM.begin(512)) {
    Serial.println("Failed to initialise EEPROM");
    Serial.println("Restarting...");
    ESP.restart();
  }
}

void write_Int_ToEeprom()
{

  //------------1---------
  if (device_status == "active") {
    EEPROM.write(60, 1);
  }
  if (device_status == "passive") {
    EEPROM.write(60, 0);
  }
  if (device_status_1 == "active") {
    EEPROM.write(61, 1);
  }
  if (device_status_1 == "passive") {
    EEPROM.write(61, 0);
  }
  if (device_status_2 == "active") {
    EEPROM.write(62, 1);
  }
  if (device_status_2 == "passive") {
    EEPROM.write(62, 0);
  }
  if (device_status_3 == "active") {
    EEPROM.write(63, 1);
  }
  if (device_status_3 == "passive") {
    EEPROM.write(63, 0);
  }
  if (device_status_4 == "active") {
    EEPROM.write(64, 1);
  }
  if (device_status_4 == "passive") {
    EEPROM.write(64, 0);
  }
  if (device_status_5 == "active") {
    EEPROM.write(65, 1);
  }
  if (device_status_5 == "passive") {
    EEPROM.write(65, 0);
  }
  if (device_status_6 == "active") {
    EEPROM.write(66, 1);
  }
  if (device_status_6 == "passive") {
    EEPROM.write(66, 0);
  }
  if (device_status_7 == "active") {
    EEPROM.write(67, 1);
  }
  if (device_status_7 == "passive") {
    EEPROM.write(67, 0);
  }
  if (device_status_8 == "active") {
    EEPROM.write(68, 1);
  }
  if (device_status_8 == "passive") {
    EEPROM.write(68, 0);
  }
  if (device_status_9 == "active") {
    EEPROM.write(69, 1);
  }
  if (device_status_9 == "passive") {
    EEPROM.write(69, 0);
  }
  if (device_status_10 == "active") {
    EEPROM.write(70, 1);
  }
  if (device_status_10 == "passive") {
    EEPROM.write(70, 0);
  }
  if (device_status_11 == "active") {
    EEPROM.write(71, 1);
  }
  if (device_status_11 == "passive") {
    EEPROM.write(71, 0);
  }
  if (device_status_12 == "active") {
    EEPROM.write(72, 1);
  }
  if (device_status_12 == "passive") {
    EEPROM.write(72, 0);
  }
  if (device_status_13 == "active") {
    EEPROM.write(73, 1);
  }
  if (device_status_13 == "passive") {
    EEPROM.write(73, 0);
  }
  if (device_status_14 == "active") {
    EEPROM.write(74, 1);
  }
  if (device_status_14 == "passive") {
    EEPROM.write(74, 0);
  }
  if (device_status_15 == "active") {
    EEPROM.write(75, 1);
  }
  if (device_status_15 == "passive") {
    EEPROM.write(75, 0);
  }
  if (device_status_16 == "active") {
    EEPROM.write(76, 1);
  }
  if (device_status_16 == "passive") {
    EEPROM.write(76, 0);
  }

  EEPROM.write(77, setting_1_value);
  EEPROM.write(78, setting_2_value);
  EEPROM.write(79, setting_3_value);
  EEPROM.write(80, setting_4_value);
  EEPROM.write(81, setting_5_value);
  EEPROM.write(82, setting_6_value);
  EEPROM.write(83, setting_7_value);
  EEPROM.write(84, setting_8_value);
  EEPROM.write(85, setting_9_value);
  EEPROM.write(86, setting_10_value);
  //EEPROM.write(87, entrance_delay_time);
  //EEPROM.write(88, exit_delay_time);
  EEPROM.write(89, alarm_time);

  //-------------1------------------
  EEPROM.write(90, int(always_on_1));
  EEPROM.write(91, int(default_settings_1));
  EEPROM.write(92, int(zone_status_1));
  EEPROM.write(93, int(sudden_alarm_1));

  //-------------2------------------
  EEPROM.write(94, int(always_on_2));
  EEPROM.write(95, int(default_settings_2));
  EEPROM.write(96, int(zone_status_2));
  EEPROM.write(97, int(sudden_alarm_2));

  //-------------3------------------
  EEPROM.write(98, int(always_on_3));
  EEPROM.write(99, int(default_settings_3));
  EEPROM.write(100, int(zone_status_3));
  EEPROM.write(101, int(sudden_alarm_3));

  //-------------4------------------
  EEPROM.write(102, int(always_on_4));
  EEPROM.write(103, int(default_settings_4));
  EEPROM.write(103, int(zone_status_4));
  EEPROM.write(105, int(sudden_alarm_4));

  EEPROM.write(106, int(test_signal_time));

  EEPROM.write(109, version);


  //  EEPROM.write(53, config_4_value);
  //  EEPROM.write(54, config_5_value);
  //  EEPROM.write(55, config_6_value);
  //  EEPROM.write(56, config_7_value);
  //  EEPROM.write(57, config_8_value);
  //  EEPROM.write(58, config_9_value);
  //  EEPROM.write(59, config_10_value);
  //  EEPROM.write(60, config_11_value);
  //  EEPROM.write(61, config_12_value);
  //  EEPROM.write(62, config_13_value);
  //  EEPROM.write(63, config_14_value);
  //  EEPROM.write(64, config_15_value);
  //  EEPROM.write(65, config_16_value);
  //  EEPROM.write(66, config_17_value);
  //  EEPROM.write(67, config_18_value);
  //  EEPROM.write(68, config_19_value);
  //  EEPROM.write(69, config_20_value);
  //  EEPROM.write(70, config_20_value);
  //  EEPROM.write(71, config_20_value);
  //  EEPROM.write(72, config_20_value);
  //  EEPROM.write(73, config_20_value);
  //  EEPROM.write(74, config_20_value);
  //  EEPROM.write(75, config_20_value);
  //  EEPROM.write(76, config_20_value);
  //  EEPROM.write(77, config_20_value);
  //  EEPROM.write(78, config_20_value);
  //  EEPROM.write(79, config_20_value);
  EEPROM.commit();
  Serial.println("Writing Datas To Eeprom");
}

void read_Int_Eeprom()
{
  if (int(EEPROM.read(60)) == 1) {
    device_status = "active";
  }
  if (int(EEPROM.read(60)) == 0) {
    device_status = "passive";
  }

  if (int(EEPROM.read(61)) == 1) {
    device_status_1 = "active";
  }
  if (int(EEPROM.read(61)) == 0) {
    device_status_1 = "passive";
  }

  if (int(EEPROM.read(62)) == 1) {
    device_status_2 = "active";
  }
  if (int(EEPROM.read(62)) == 0) {
    device_status_2 = "passive";
  }

  if (int(EEPROM.read(63)) == 1) {
    device_status_3 = "active";
  }
  if (int(EEPROM.read(63)) == 0) {
    device_status_3 = "passive";
  }

  if (int(EEPROM.read(64)) == 1) {
    device_status_4 = "active";
  }
  if (int(EEPROM.read(64)) == 0) {
    device_status_4 = "passive";
  }

  if (int(EEPROM.read(65)) == 1) {
    device_status_5 = "active";
  }
  if (int(EEPROM.read(65)) == 0) {
    device_status_5 = "passive";
  }

  if (int(EEPROM.read(66)) == 1) {
    device_status_6 = "active";
  }
  if (int(EEPROM.read(66)) == 0) {
    device_status_6 = "passive";
  }

  if (int(EEPROM.read(67)) == 1) {
    device_status_7 = "active";
  }
  if (int(EEPROM.read(67)) == 0) {
    device_status_7 = "passive";
  }

  if (int(EEPROM.read(68)) == 1) {
    device_status_8 = "active";
  }
  if (int(EEPROM.read(68)) == 0) {
    device_status_8 = "passive";
  }

  if (int(EEPROM.read(69)) == 1) {
    device_status_9 = "active";
  }
  if (int(EEPROM.read(69)) == 0) {
    device_status_9 = "passive";
  }

  if (int(EEPROM.read(70)) == 1) {
    device_status_10 = "active";
  }
  if (int(EEPROM.read(70)) == 0) {
    device_status_10 = "passive";
  }

  if (int(EEPROM.read(71)) == 1) {
    device_status_11 = "active";
  }
  if (int(EEPROM.read(71)) == 0) {
    device_status_11 = "passive";
  }

  if (int(EEPROM.read(72)) == 1) {
    device_status_12 = "active";
  }
  if (int(EEPROM.read(72)) == 0) {
    device_status_12 = "passive";
  }

  if (int(EEPROM.read(73)) == 1) {
    device_status_13 = "active";
  }
  if (int(EEPROM.read(73)) == 0) {
    device_status_13 = "passive";
  }

  if (int(EEPROM.read(74)) == 1) {
    device_status_14 = "active";
  }
  if (int(EEPROM.read(74)) == 0) {
    device_status_14 = "passive";
  }

  if (int(EEPROM.read(75)) == 1) {
    device_status_15 = "active";
  }
  if (int(EEPROM.read(75)) == 0) {
    device_status_15 = "passive";
  }

  if (int(EEPROM.read(76)) == 1) {
    device_status_16 = "active";
  }
  if (int(EEPROM.read(76)) == 0) {
    device_status_16 = "passive";
  }
  setting_1_value = int(EEPROM.read(77));
  setting_2_value = int(EEPROM.read(78));
  setting_3_value = int(EEPROM.read(79));
  setting_4_value = int(EEPROM.read(80));
  setting_5_value = int(EEPROM.read(81));
  setting_6_value = int(EEPROM.read(82));
  setting_7_value = int(EEPROM.read(83));
  setting_8_value = int(EEPROM.read(84));
  setting_9_value = int(EEPROM.read(85));
  setting_10_value = int(EEPROM.read(86));
  //  entrance_delay_time = int(EEPROM.read(87));
  //  exit_delay_time = int(EEPROM.read(88));
  alarm_time = int(EEPROM.read(89));

  //--------------1--------------
  always_on_1 = int(EEPROM.read(90));
  default_settings_1 = int(EEPROM.read(91));
  zone_status_1 = int(EEPROM.read(92));
  sudden_alarm_1 = int(EEPROM.read(93));

  //--------------2--------------
  always_on_2 = int(EEPROM.read(94));
  default_settings_2 = int(EEPROM.read(95));
  zone_status_2 = int(EEPROM.read(96));
  sudden_alarm_2 = int(EEPROM.read(97));

  //--------------3--------------
  always_on_3 = int(EEPROM.read(98));
  default_settings_3 = int(EEPROM.read(99));
  zone_status_3 = int(EEPROM.read(100));
  sudden_alarm_3 = int(EEPROM.read(101));

  //--------------4--------------
  always_on_4 = int(EEPROM.read(102));
  default_settings_4 = int(EEPROM.read(103));
  zone_status_4 = int(EEPROM.read(104));
  sudden_alarm_4 = int(EEPROM.read(105));

  test_signal_time = int(EEPROM.read(106));

  device_http_counter = int(EEPROM.read(107));
  last_device_http_counter = int(EEPROM.read(108));

  version = int(EEPROM.read(109));

  //  config_4_value = int(EEPROM.read(53));
  //  config_5_value = int(EEPROM.read(54));
  //  config_6_value = int(EEPROM.read(55));
  //  config_7_value = int(EEPROM.read(56));
  //  config_8_value = int(EEPROM.read(57));
  //  config_9_value = int(EEPROM.read(58));
  //  config_10_value = int(EEPROM.read(59));
  //  config_11_value = int(EEPROM.read(60));
  //  config_12_value = int(EEPROM.read(61));
  //  config_13_value = int(EEPROM.read(62));
  //  config_14_value = int(EEPROM.read(63));
  //  config_15_value = int(EEPROM.read(64));
  //  config_16_value = int(EEPROM.read(65));
  //  config_17_value = int(EEPROM.read(66));
  //  config_18_value = int(EEPROM.read(67));
  //  config_19_value = int(EEPROM.read(68));
  //  config_20_value = int(EEPROM.read(69));
  //  config_21_value = int(EEPROM.read(70));
  //  config_22_value = int(EEPROM.read(71));
  //  config_23_value = int(EEPROM.read(72));
  //  config_24_value = int(EEPROM.read(73));
  //  config_25_value = int(EEPROM.read(74));
  //  config_26_value = int(EEPROM.read(75));
  //  config_27_value = int(EEPROM.read(76));
  //  config_28_value = int(EEPROM.read(77));
  //  config_29_value = int(EEPROM.read(78));
  //  config_30_value = int(EEPROM.read(79));

  charge_counter = pow(setting_1_value, 3);
  sum_of_power = pow(setting_2_value, 3);
  entrance_delay_time = pow(setting_3_value, 3);

  Serial.println("-----------Read Eeprom Int Values-------------------------");
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
  Serial.print("test_signal_time:");
  Serial.println(test_signal_time);
  Serial.print("device_http_counter:");
  Serial.println(device_http_counter);
  Serial.print("last_device_http_counter:");
  Serial.println(last_device_http_counter);
  Serial.print("version:");
  Serial.println(version);
}
