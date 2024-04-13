unsigned long previousMillis_swser1_send = 0;
const long interval_swser1_send = 1000;
int counter = 0;

void swSer1_Send_Data() {
//  unsigned long currentMillis = millis();
//  if (currentMillis - previousMillis_swser1_send >= interval_swser1_send) {
//    previousMillis_swser1_send = currentMillis;
//
//    counter ++;
//    if (counter == 1) {
//      if (ble_status == 0) {
//        swSer_1.println("w" + String(wifi_status) + "s1-" + String(sensor_1_value) + "s2-" + String(sensor_2_value) + "s3-" + String(sensor_3_value)
//                        + "s4-" + String(sensor_4_value) + "s5-" + String(sensor_5_value) + "s6-" + String(sensor_6_value)
//                        + "r12-" + relay_12_cloud_value
//                        + "r13-" + relay_13_cloud_value + "r14-" + relay_14_cloud_value + "r15-" + relay_15_cloud_value
//                        + "r16-" + relay_16_cloud_value + "int");
//      }
//
//
//      if (ble_status == 1) {
//        swSer_1.println("w" + String(wifi_status) + "s1-" + String(sensor_1_value) + "s2-" + String(sensor_2_value) + "s3-" + String(sensor_3_value)
//                        + "s4-" + String(sensor_4_value) + "s5-" + String(sensor_5_value) + "s6-" + String(sensor_6_value)
//                        + "ble_work");
//      }
//    }
//    if (counter == 2) {
//      swSer_1.println("m-" + String(manuel_auto_value) + "w1m-" + String(win1_max_open_time) + "w2m-" + String(win2_max_open_time) + "wo1-" + String(open_window_1) + "wo2-" + String(open_window_2) + "+");
//      counter = 0;
//    }
//  }
//}
//
//void swSer1_Send_Reset_Data() {
//  //swSer_1.println("sysrs" + String(sys_reset_value) + "gsmrs" + String(gsm_reset_value) + "?");
}
