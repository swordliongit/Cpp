//unsigned long previousMillis_ntc_timer = 0;
//const long interval_ntc_timer = 300000;
//
//// Variables to save date and time
//String formattedDate;
//
//void wifi_Ntc_Time_Setup() {
//  if (WiFi.status() == WL_CONNECTED) {
//    while (!timeClient.update()) {
//      timeClient.forceUpdate();
//    }
//    // The formattedDate comes with the following format:
//    // 2018-05-28T16:00:13Z
//    // We need to extract date and time
//    formattedDate = timeClient.getFormattedDate();
//    Serial.println(formattedDate);
//    wifi_Time_Parse();
//  }
//}
//
//void wifi_Ntc_Time() {
//  if (WiFi.status() == WL_CONNECTED) {
//    unsigned long currentMillis = millis();
//    if (currentMillis - previousMillis_ntc_timer >= interval_ntc_timer) {
//      previousMillis_ntc_timer = currentMillis;
//      while (!timeClient.update()) {
//        timeClient.forceUpdate();
//      }
//      // The formattedDate comes with the following format:
//      // 2018-05-28T16:00:13Z
//      // We need to extract date and time
//      formattedDate = timeClient.getFormattedDate();
//      Serial.println(formattedDate);
//      wifi_Time_Parse();
//    }
//  }
//}
//
//void wifi_Time_Parse() {
//  if (formattedDate.indexOf("T") > 0 ) {
//    String year = (formattedDate.substring(2, 4));
//    te.Year = atoi (year.c_str ());
//    String month = (formattedDate.substring(5, 7));
//    te.Month = atoi (month.c_str ());
//    String day = (formattedDate.substring(8, 10));
//    te.Day = atoi (day.c_str ());
//    String hour = (formattedDate.substring(11, 13));
//    te.Hour = atoi (hour.c_str ());
//    String minute = (formattedDate.substring(14, 16));
//    te.Minute = atoi (minute.c_str ());
//    String second = (formattedDate.substring(17, 19));
//    te.Second = atoi (second.c_str ());
//    setTime(hour.toInt(), minute.toInt(), second.toInt(), day.toInt(), month.toInt(), year.toInt());
//    date_time_now = String(year.toInt()) + "-" + String(month.toInt()) + "-" + String(day.toInt()) + " " + String(hour.toInt()) + ":" + String(minute.toInt()) + ":" + String(second.toInt());
//    unixTime =  makeTime(te) + 946767600;
//    timestamp = String(unixTime);
//    Serial.print("Timestamp=");
//    Serial.println(timestamp);
//  }
//}
