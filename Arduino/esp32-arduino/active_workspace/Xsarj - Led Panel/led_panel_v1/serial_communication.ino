//void serial2_Send_Data() {
//  Serial2.println("aaa");
//}


// function prototypes
void anim_StationReserved(PatternAnimator& p10, double cycle);
void anim_StationWaiting(PatternAnimator& p10, double cycle);
void anim_StationStopped(PatternAnimator& p10, double cycle);
void anim_StationCharging(PatternAnimator& p10, double cycle);


void serial2_get_data(PatternAnimator& p10, DMD& dmd) 
{
    if (Serial2.available() > 0) 
    {
        data_from_serial2 = Serial2.readStringUntil('\n');
        if(data_from_serial2 == "1")
            anim_StationWaiting(p10, 1);
        else if(data_from_serial2 == "2")
            anim_StationCharging(p10, 1);
        else if(data_from_serial2 == "3")
            anim_StationStopped(p10, 1);
        else if(data_from_serial2 == "4")
            anim_StationReserved(p10, 1);
        else
            ;

        yield();
        Serial.println("Raw Serial-2 Data: " + data_from_serial2);
        data_from_serial2 = data_from_serial2.substring(data_from_serial2.indexOf("p_") + 2, data_from_serial2.indexOf("!"));
        screen_test_string = data_from_serial2;
    }
}
