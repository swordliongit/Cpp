//void serial2_Send_Data() {
//  Serial2.println("aaa");
//}


// function prototypes
void anim_StationReserved(PatternAnimator& p10, double cycle);
void anim_StationWaiting(PatternAnimator& p10, double cycle);
void anim_StationStopped(PatternAnimator& p10, double cycle);
void anim_StationCharge_Charging(PatternAnimator& p10, double cycle);
void anim_StationCharge_Starting();
void anim_StationCharge_Started();
void anim_StationCharge_Stopped();

bool charge_started = false;
bool charge_stopped = false;

void serial2_get_data(PatternAnimator& p10, DMD& dmd) 
{
    if (Serial2.available() > 0) 
    {
        data_from_serial2 = Serial2.readStringUntil('\n');
        if(data_from_serial2 == "1")
        {
            charge_started = false;
            if(!charge_stopped)
            {
                anim_StationCharge_Stopped();
                charge_stopped = true;
            }
            anim_StationWaiting(p10, 1);
        }
        else if(data_from_serial2 == "2")
        {
            charge_stopped = false;
            if(!charge_started)
            {
                anim_StationCharge_Starting();
                anim_StationCharge_Started();
                charge_started = true;
            }
            anim_StationCharge_Charging(p10, 1);
        }
        else if(data_from_serial2 == "3")
        {
            charge_started = false;
            charge_stopped = false;
            anim_StationStopped(p10, 1);
        }
        else if(data_from_serial2 == "4")
        {
            charge_started = false;
            charge_stopped = false;
            anim_StationReserved(p10, 1);
        }

        yield();
        Serial.println("Raw Serial-2 Data: " + data_from_serial2);
        data_from_serial2 = data_from_serial2.substring(data_from_serial2.indexOf("p_") + 2, data_from_serial2.indexOf("!"));
        screen_test_string = data_from_serial2;
    }
}
