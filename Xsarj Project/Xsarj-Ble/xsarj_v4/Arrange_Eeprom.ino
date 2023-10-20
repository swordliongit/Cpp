void change_wifi_Command() {
  String data = second_esp_serial_data;
  Serial.println("here1");
  writeStringToEeprom(1, data);
  arrangeWifiAndPassword();
  if (data.startsWith("chwifi")) {
    delay(5);
    ESP.restart();
  }
}

void arrangeWifiAndPassword() {
  String recivedData;
  recivedData = read_StringFromEeprom(1);
  Serial.print("Read Wifi Data:");
  Serial.println(recivedData);
  if (recivedData.startsWith("chwifi")) {
    String wifiname = (recivedData.substring(recivedData.indexOf("chwifi") + 6, recivedData.indexOf("-")));
    String wifipassword = (recivedData.substring(recivedData.indexOf("-") + 1, recivedData.indexOf("%")));
    wifiname.toCharArray(ssid, 50);
    wifipassword.toCharArray(password, 50);
  }
  if (recivedData.startsWith("sop:")) {
    sum_of_power = (recivedData.substring(recivedData.indexOf("sop:") + 4, recivedData.indexOf("cc:"))).toDouble();
    charge_counter = (recivedData.substring(recivedData.indexOf("cc:") + 3, recivedData.indexOf("r1:"))).toDouble();
    relay_1_cloud_value = (recivedData.substring(recivedData.indexOf("r1:") + 3, recivedData.indexOf("ptp:")));
    partner_total_payment = (recivedData.substring(recivedData.indexOf("ptp:") + 4, recivedData.indexOf("pp:"))).toFloat();
    package_price_1 = (recivedData.substring(recivedData.indexOf("pp:") + 3, recivedData.indexOf("!"))).toFloat();
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
//
//void tryToReconnectWifi_Setup() {
//  if (WiFi.status() != WL_CONNECTED) {
//    Serial.println("WiFi not connected. Trying to connecting..");
//    WiFi.disconnect();
//    WiFi.mode(WIFI_OFF);
//    WiFi.mode(WIFI_STA);
//    WiFi.begin(ssid, password);
//    if (WiFi.waitForConnectResult() != WL_CONNECTED) {
//      Serial.printf("WiFi Failed!\n");
//      return;
//    }
//    WiFi.setSleep(false);
//  }
//  if (WiFi.status() == WL_CONNECTED) {
//    wifi_connected_counter++;
//    wifi_status = 1;
//  }
//}
//
//
//void tryToReconnectWifi() {
//  unsigned long currentMillis = millis();
//  if (currentMillis - previousMillis_wifi_timer >= interval_wifi_timer) {
//    previousMillis_wifi_timer = currentMillis;
//    unsigned long currentMillis = millis();
//    if (WiFi.status() != WL_CONNECTED) {
//      Serial.println("WiFi not connected. Trying to connecting..");
//      WiFi.disconnect();
//      WiFi.mode(WIFI_OFF);
//      WiFi.mode(WIFI_STA);
//      WiFi.begin(ssid, password);
//      //    if (WiFi.waitForConnectResult() != WL_CONNECTED) {
//      //      Serial.printf("WiFi Failed!\n");
//      //      return;
//      //    }
//      WiFi.setSleep(false);
//    }
//    if (wifi_connected_counter == 0 && WiFi.status() == WL_CONNECTED) {
//      ESP.restart();
//    }
//  }
//}


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
  while (k != '\0' && len < 500) //Read until null character
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
  EEPROM.write(60, 0);
  EEPROM.write(61, 0);
  EEPROM.write(62, 0);
  EEPROM.write(63, 0);
  EEPROM.write(64, 0);
  EEPROM.commit();
  ESP.restart();
}

void testEepromWorking() {
  if (!EEPROM.begin(350)) {
    Serial.println("Failed to initialise EEPROM");
    Serial.println("Restarting...");
    ESP.restart();
  }
}

void write_Int_ToEeprom()
{
  EEPROM.write(60, config_1_value);
  EEPROM.write(61, config_2_value);
  EEPROM.write(62, config_3_value);
  EEPROM.write(63, config_4_value);
  EEPROM.write(64, config_5_value);
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
  config_1_value = int(EEPROM.read(60));
  config_2_value = int(EEPROM.read(61));
  config_3_value = int(EEPROM.read(62));
  config_4_value = int(EEPROM.read(63));
  config_5_value = int(EEPROM.read(64));
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


  Serial.println("Read Eeprom Int Values: ");
  Serial.print("config_1_value: ");
  Serial.println(config_1_value);
  Serial.print("config_2_value: ");
  Serial.println(config_2_value);
  Serial.print("config_3_value: ");
  Serial.println(config_3_value);
  Serial.print("config_4_value: ");
  Serial.println(config_4_value);
  Serial.print("config_5_value: ");
  Serial.println(config_5_value);
  charge_counter = pow(config_1_value, 3);
  sum_of_power = pow(config_2_value, 3);
  //relay_1_cloud_value = String(pow(config_3_value, 3));
  partner_total_payment = pow(config_4_value, 3);
  package_price_1 = pow(config_5_value, 3);
  Serial.print("charge_counter_eeprom: ");
  Serial.println(charge_counter);
}
