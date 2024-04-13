//int battery_http_counter = 0;
//int last_battery_http_counter = 0;
//void battery_Status() {
//  if (sensor_10_value < 2800) {
//    battery_http_counter = 1;
//    if (battery_http_counter != last_battery_http_counter) {
//      ademco_id = "E302-000";
//      gsm_ademco_id = "E302-000&gsm";
//      if (wifi_Http_Post_Request_Create_Emergency(true) == 1) {
//        Serial.println("Ademco Send To Server E302-000 Low Battery");
//        last_battery_http_counter = battery_http_counter;
//      }
//    }
//    ademco_id = "E602-000";
//  }
//  if (sensor_10_value >= 3000) {
//    battery_http_counter = 0;
//    if (battery_http_counter != last_battery_http_counter) {
//      ademco_id = "R302-000";
//      gsm_ademco_id = "R302-000&gsm";
//      if (wifi_Http_Post_Request_Create_Emergency(true) == 1) {
//        Serial.println("Ademco Send To Server R302-000 Low Battery Came Normal");
//        last_battery_http_counter = battery_http_counter;
//      }
//    }
//    ademco_id = "E602-000";
//  }
//}
