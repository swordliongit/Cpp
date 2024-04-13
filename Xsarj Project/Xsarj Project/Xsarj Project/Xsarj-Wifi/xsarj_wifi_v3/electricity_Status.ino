//int electricity_http_counter = 0;
//int last_electricity_http_counter = 0;
//void electricity_Status() {
//  if (sensor_9_value < 3000) {
//    electricity_http_counter = 1;
//    if (electricity_http_counter != last_electricity_http_counter) {
//      ademco_id = "E301-000";
//      gsm_ademco_id = "E301-000&gsm";
//      if (wifi_Http_Post_Request_Create_Emergency(true) == 1) {
//        Serial.println("Ademco Send To Server E301-000 Electricity Cut");
//        last_electricity_http_counter = electricity_http_counter;
//      }
//    }
//    ademco_id = "E602-000";
//  }
//  if (sensor_9_value >= 3000) {
//    electricity_http_counter = 0;
//    if (electricity_http_counter != last_electricity_http_counter) {
//      ademco_id = "R301-000";
//      gsm_ademco_id = "R301-000&gsm";
//      if (wifi_Http_Post_Request_Create_Emergency(true) == 1) {
//        Serial.println("Ademco Send To Server R301-000 Electricity Cut Came Normal");
//        last_electricity_http_counter = electricity_http_counter;
//      }
//    }
//    ademco_id = "E602-000";
//  }
//}
