/*--------------------------------------------------------------------------------------

  dmd_test.cpp
   Demo and example project for the Freetronics DMD, a 512 LED matrix display
   panel arranged in a 32 x 16 layout.

  This LIibrary (DMD32) and example are  fork of original DMD library  was modified to work on ESP32
  Modified by: Khudhur Alfarhan  // Qudoren@gmail.com
  1/Oct./2020

  See http://www.freetronics.com/dmd for resources and a getting started guide.

  Note that the DMD32 library uses the VSPI port for the fastest, low overhead writing to the
  display. Keep an eye on conflicts if there are any other devices running from the same
  SPI port, and that the chip select on those devices is correctly set to be inactive
  when the DMD is being written to.

  USAGE NOTES
  -----------
  - Place the DMD library folder into the "arduino/libraries/" folder of your Arduino installation.
  - Restart the IDE.
  - In the Arduino IDE, go to Tools > Board > and choose any ESP32 board
  - In the Arduino IDE, you can open File > Examples > DMD > dmd_demo, or dmd_clock_readout, and get it
   running straight away!

   See the documentation on Github or attached images to find the pins that should be connected to the DMD LED display


  This example code is in the public domain.
  The DMD32 library is open source (GPL), for more see DMD32.cpp and DMD32.h

  --------------------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------------------
  Includes
  --------------------------------------------------------------------------------------*/
#include "esp_system.h"
#include <DMD32.h>        //
#include "fonts/SystemFont5x7.h"
#include "fonts/Arial_black_16.h"
#include "fonts/Arial14.h"

#include <vector> // for vector
#include <limits> // for numeric_limits
#include <thread>

#include <pthread.h>


#include <p10_animations_kilicarslan.h>
// #include "p10_animations/p10_animations.h"

String data_from_serial2 = "";
char screen_test_char[] = "test";
String screen_test_string = "XSarj";

TaskHandle_t Task1;
TaskHandle_t Task2;


const int wdtTimeout = 60000;  //time in ms to trigger the watchdog
hw_timer_t *timer = NULL;

void IRAM_ATTR resetModule() {
    ets_printf("reboot\n");
    esp_restart();
}

char uniquename[15]; //Create a Unique AP from MAC address
char uniqueid[15];
String id;

//Fire up the DMD library as dmd
#define DISPLAYS_ACROSS 2
#define DISPLAYS_DOWN 1
DMD dmd(DISPLAYS_ACROSS, DISPLAYS_DOWN);

/*--------------------------------------------------------------------------------------
  Interrupt handler for Timer1 (TimerOne) driven DMD refresh scanning, this gets
  called at the period set in Timer1.initialize();
  --------------------------------------------------------------------------------------*/
void IRAM_ATTR triggerScan()
{
    dmd.scanDisplayBySPI();
}

/*--------------------------------------------------------------------------------------
  setup
  Called by the Arduino architecture before the main loop begins
  --------------------------------------------------------------------------------------*/
void setup(void)
{
    Serial.begin(115200);
    Serial2.begin(9600);
    //Serial2.begin(115200);

    createSSID();
    Serial.println("Device Id = " + id);


    // return the clock speed of the CPU
    uint8_t cpuClock = ESP.getCpuFreqMHz();
    // Use 1st timer of 4
    // devide cpu clock speed on its speed value by MHz to get 1us for each signal  of the timer
    timer = timerBegin(0, cpuClock, true);
    // Attach triggerScan function to our timer
    timerAttachInterrupt(timer, &triggerScan, true);
    // Set alarm to call triggerScan function
    // Repeat the alarm (third parameter)
    timerAlarmWrite(timer, 300, true);
    // Start an alarm
    timerAlarmEnable(timer);
    //clear/init the DMD pixels held in RAM
    dmd.clearScreen( true );   //true is normal (all pixels off), false is negative (all pixels on)

    // pthread_t threads[4];
    // pthread_create(&threads[0], NULL, TCB1, NULL);
    // pthread_create(&threads[1], NULL, TCB2, NULL);
    // pthread_create(&threads[2], NULL, TCB3, NULL);
    // pthread_create(&threads[3], NULL, TCB4, NULL);
}

void anim_StationReserved(PatternAnimator& p10, double cycle=std::numeric_limits<double>::infinity())
{
    int ROW_START = 4;
    int COL_START = 23;
    int msdelay = 250;

    // hourglass frame
    p10.draw_pattern_static(p10.hourglass, ROW_START, COL_START);
    // animation loop
    while(cycle > 0)
    {
        ROW_START = 5;
        COL_START = 26;
        p10.draw_pattern_static(p10.hourglass_anim_start, ROW_START, COL_START);
        delay(msdelay);
        p10.delete_pattern_static(p10.hourglass_anim_start, ROW_START, COL_START);
        p10.draw_pattern_static(p10.hourglass_anim_phase_first, ROW_START, COL_START);
        delay(msdelay);
        p10.delete_pattern_static(p10.hourglass_anim_phase_first, ROW_START, COL_START);
        p10.draw_pattern_static(p10.hourglass_anim_phase_second, ROW_START, COL_START);
        delay(msdelay);
        p10.delete_pattern_static(p10.hourglass_anim_phase_second, ROW_START, COL_START);
        p10.draw_pattern_static(p10.hourglass_anim_phase_third, ROW_START, COL_START);
        delay(msdelay);
        p10.delete_pattern_static(p10.hourglass_anim_phase_third, ROW_START, COL_START);
        p10.draw_pattern_static(p10.hourglass_anim_phase_last, ROW_START, COL_START);
        delay(msdelay);
        --cycle;
    }
}

void anim_StationWaiting(PatternAnimator& p10, double cycle=std::numeric_limits<double>::infinity())
{
    int ROW_START = 4;
    int COL_START = 0;
    int PANEL_LAST_COL = 55;
    int msdelay = 4000;
    int delaystep = 25;
    p10.draw_pattern_tetris(p10.xsarj, ROW_START, COL_START, PANEL_LAST_COL, msdelay, cycle);
    dmd.clearScreen(true);
    COL_START = 55;
    p10.draw_pattern_scrolling(p10.xsarj, ROW_START, COL_START, delaystep, cycle);
}

// *********************************
// Station Stopped( chargehandle )
// *********************************
// to pass multiple arguments to the thread function
struct pDrawerArgs
{
    int msdelay;
    double cycle;
};
void anim_StationStopped(PatternAnimator& p10, double cycle=std::numeric_limits<double>::infinity())
{
    int ROW_START = 0;
    int COL_START = 0;
    int msdelay = 0;
    int delaystep = 0;

    pDrawerArgs args1, args2;
    pthread_t chargehandle_animator[2];

    msdelay = 100;
    delaystep = 25;
    args1.msdelay = msdelay;
    args1.cycle = cycle+16;
    pthread_create(&chargehandle_animator[0], NULL, parallel_drawer_chargehandle, &args1);

    msdelay = 250;
    args2.msdelay = msdelay;
    args2.cycle = cycle+6;
    pthread_create(&chargehandle_animator[1], NULL, parallel_drawer_chargehandle_cable, &args2);

    ROW_START = 4;
    COL_START = 3;
    msdelay = 400;
    p10.draw_pattern_blinking(p10.excmark_little, ROW_START, COL_START, msdelay, cycle);
}
void* parallel_drawer_chargehandle_cable(void* thread_ptr)
{
    int ROW_START = 4;
    int COL_START = 26;
    PatternAnimator p10(&dmd);

    pDrawerArgs* args = static_cast<pDrawerArgs*>(thread_ptr);
    int msdelay = args->msdelay;
    int cycle = args->cycle;
    // delay(4000);
    // var = *(static_cast<type*>(pattern_ptr));
    while(cycle > 0)
    {
        p10.draw_pattern_static(p10.chargehandle_cable_frame_1, ROW_START, COL_START);
        delay(msdelay);
        p10.draw_pattern_static(p10.chargehandle_cable_frame_2, ROW_START, COL_START);
        delay(msdelay);
        --cycle;
    }
}
void* parallel_drawer_chargehandle(void* thread_ptr)
{
    int ROW_START = 4;
    int COL_START = 41;
    PatternAnimator p10(&dmd);

    pDrawerArgs* args = static_cast<pDrawerArgs*>(thread_ptr);
    int msdelay = args->msdelay;
    int cycle = args->cycle;
    // delay(4000);
    // var = *(static_cast<type*>(pattern_ptr));
    while(cycle > 0)
    {
        p10.draw_pattern_static(p10.chargehandle_frame_1, ROW_START, COL_START);
        delay(msdelay);
        p10.draw_pattern_static(p10.chargehandle_frame_2, ROW_START, COL_START);
        delay(msdelay);
        p10.draw_pattern_static(p10.chargehandle_frame_3, ROW_START, COL_START);
        delay(msdelay);
        --cycle;
    }
}
// *********************************
// *********************************

void anim_StationCharging(PatternAnimator& p10, double cycle=std::numeric_limits<double>::infinity())
{
    int ROW_START = 4;
    int COL_START = 0;
    int delaystep = 35;
    p10.draw_pattern_scrolling(p10.arrow_single, ROW_START, COL_START, delaystep, cycle);
}

void runthreads()
{

    // //create a task that will be executed in the Task1code() function, with priority 1 and executed on core 0
    // xTaskCreatePinnedToCore(
    //                     Task1code,   /* Task function. */
    //                     "Task1",     /* name of task. */
    //                     10000,       /* Stack size of task */
    //                     NULL,        /* parameter of the task */
    //                     1,           /* priority of the task */
    //                     &Task1,      /* Task handle to keep track of created task */
    //                     0);          /* pin task to core 0 */                  

    // //create a task that will be executed in the Task2code() function, with priority 1 and executed on core 1
    // xTaskCreatePinnedToCore(
    //                     Task2code,   /* Task function. */
    //                     "Task2",     /* name of task. */
    //                     10000,       /* Stack size of task */
    //                     NULL,        /* parameter of the task */
    //                     1,           /* priority of the task */
    //                     &Task2,      /* Task handle to keep track of created task */
    //                     1);          /* pin task to core 1 */
}


/*--------------------------------------------------------------------------------------
  loop
  Arduino architecture main loop
  --------------------------------------------------------------------------------------*/
void loop(void)
{
	byte b;

	// 10 x 14 font clock, including demo of OR and NOR modes for pixels so that the flashing colon can be overlayed
	dmd.clearScreen( true );
	dmd.selectFont(System5x7);

    

    int ROW_START = 4;

    int COL_START = 0;
    int pxjmp_step = 0;
    int msdelay = 0;
    int PANEL_LAST_COL = 0;
    int cycle = 0;
    float delaystep = 35;

    // anim_StationStopped();
    COL_START = 0;
    int PATTERN_DISTANCE = 10;

    PatternAnimator p10(&dmd);

    // p10.draw_pattern_scrolling(p10.xsarj, ROW_START, COL_START, 35);

    p10.pattern_pack.push_back(p10.arrow_single);
    p10.pattern_pack.push_back(p10.arrow_single);
    p10.pattern_pack.push_back(p10.arrow_single);

    delaystep = 35;


    while(true)
    {
        // p10.draw_pattern_scrolling_accumulator_series(p10.pattern_pack, ROW_START, COL_START, 1, delaystep);
        anim_StationWaiting(p10, 1);
        // dmd.clearScreen(true);
        // anim_StationStopped(p10, 10);
        // dmd.clearScreen(true);
        // anim_StationReserved(p10, 2);
        // dmd.clearScreen(true);
        // anim_StationCharging(p10, 2);
        // dmd.clearScreen(true);
    }

    // PatternAnimator p10(&dmd);
    // p10.draw_pattern_scrolling_rotating(p10.sword, ROW_START, COL_START, delaystep);



    // runthreads();



	delay(3600000);

	serial2_get_data();
}
