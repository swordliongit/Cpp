//void serial2_Send_Data() {
//  Serial2.println("aaa");
//}


// function prototypes
// void anim_StationReserved(PatternAnimator& p10, double cycle);
// void anim_StationWaiting(PatternAnimator& p10, double cycle);
// void anim_StationStopped(PatternAnimator& p10, double cycle);
// void anim_StationCharge_Charging(PatternAnimator& p10, double cycle);
// void anim_StationCharge_Starting();
// void anim_StationCharge_Started();
// void anim_StationCharge_Stopped();


void serial2_get_data() {
    if (Serial2.available() > 0) {
        raw_serial2 = Serial2.readStringUntil('\n');
        Serial.println("raw_serial2: " + raw_serial2);
        if (raw_serial2.indexOf("p_") >= 0 && raw_serial2.indexOf("!") >= 0) {
            screen_test_string = raw_serial2.substring(raw_serial2.indexOf("p_") + 2, raw_serial2.indexOf("!"));
            Serial.println("screen_test_string: " + screen_test_string);
            yield();
        }
        if (raw_serial2.indexOf("pst_") >= 0 && raw_serial2.indexOf("!") >= 0) {
            data_from_serial2 = raw_serial2.substring(raw_serial2.indexOf("pst_") + 4, raw_serial2.indexOf("!"));
            Serial.println("data_from_serial2: " + data_from_serial2);
            //screen_test_string = data_from_serial2;
            yield();
        }
        // change_wifi_Command();
    }
}
