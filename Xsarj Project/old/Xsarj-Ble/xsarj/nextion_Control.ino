//unsigned long previousMillis_send_data_nextion = 0;
//const long interval_send_data_nextion = 20000;
//
//void nextion_Control() {
//  String message = myNextion.listen();
//  if (message != "") { // if a message is received...
//    Serial.println(message); //...print it out
//  }
//  nextion_Send_Data_Periodic();
//}
//
//void nextion_Send_Data_Periodic() {
//  unsigned long currentMillis = millis();
//  if (currentMillis - previousMillis_send_data_nextion >= interval_send_data_nextion) {
//    previousMillis_send_data_nextion = currentMillis;
//    //myNextion.sendCommand("page page9");
//    myNextion.setComponentValue("n0", sensor_7_value);
//    myNextion.setComponentValue("n1", sensor_8_value);
//    myNextion.setComponentValue("n2", sensor_3_value * 0.128);
//    myNextion.setComponentValue("n3", sensor_13_value / 20);
//    myNextion.setComponentValue("n4", sensor_12_value / 4095);
//    myNextion.setComponentValue("n5", sensor_7_value);
//    myNextion.setComponentValue("n6", sensor_9_value);
//    myNextion.setComponentValue("n7", sensor_10_value);
//  }
//}
