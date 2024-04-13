//void serial2_Send_Data() {
//  Serial2.println("aaa");
//}
//
void serial2_get_data() {
  if (Serial2.available() > 0) {
    data_from_serial2 = Serial2.readStringUntil('\n');
    yield();
      Serial.println("Raw Serial-2 Data: " + data_from_serial2);
      data_from_serial2 = data_from_serial2.substring(data_from_serial2.indexOf("p_") + 2, data_from_serial2.indexOf("!"));
      screen_test_string = data_from_serial2;
  }
}
