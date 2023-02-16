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
#include <vector>


#include <p10_animations_kilicarslan.h>
// #include "p10_animations/p10_animations.h"

String data_from_serial2 = "";
char screen_test_char[] = "test";
String screen_test_string = "XSarj";

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

    timer = timerBegin(0, 80, true);                  //timer 0, div 80
    timerAttachInterrupt(timer, &resetModule, true);  //attach callback
    timerAlarmWrite(timer, wdtTimeout * 5000, false); //set time in us
    timerAlarmEnable(timer);                          //enable interrupt
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

}

//16x64
std::vector<std::vector<int>> xsarj_full = 
{
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,1,1,0,0,0,0,1,1,1,0,0,0,1,1,1,1,0,0,0,1,1,0,0,0,1,1,1,1,1,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,1,1,0,0,1,1,1,0,0,0,1,1,1,0,0,0,0,1,0,0,1,0,0,1,0,0,0,1,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,1,1,1,1,1,0,0,0,0,1,1,1,0,0,0,1,1,0,0,1,1,0,1,0,0,1,1,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,1,1,1,0,0,0,0,0,0,0,1,1,0,0,1,0,0,0,0,1,0,1,1,1,1,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,1,0,1,1,1,0,0,0,0,0,0,1,1,1,0,1,1,1,1,1,1,0,1,0,0,1,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,1,1,0,0,1,1,1,0,0,0,1,1,1,1,0,0,1,0,0,0,0,1,0,1,0,0,1,1,0,1,1,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,1,1,0,0,0,0,1,1,1,0,0,0,0,1,1,0,0,1,0,0,0,0,1,0,1,0,0,0,1,0,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
};
//7x35
std::vector<std::vector<int>> xsarj = 
{
    {1,1,0,0,0,0,1,1,1,0,0,0,1,1,1,1,0,0,0,1,1,0,0,0,1,1,1,1,1,0,0,0,0,1,1},
    {0,1,1,0,0,1,1,1,0,0,0,1,1,1,0,0,0,0,1,0,0,1,0,0,1,0,0,0,1,0,0,0,0,1,1},
    {0,0,1,1,1,1,1,0,0,0,0,1,1,1,0,0,0,1,1,0,0,1,1,0,1,0,0,1,1,0,0,0,0,1,1},
    {0,0,0,1,1,1,0,0,0,0,0,0,0,1,1,0,0,1,0,0,0,0,1,0,1,1,1,1,0,0,0,0,0,1,1},
    {0,0,1,0,1,1,1,0,0,0,0,0,0,1,1,1,0,1,1,1,1,1,1,0,1,0,0,1,0,0,0,0,0,1,1},
    {0,1,1,0,0,1,1,1,0,0,0,1,1,1,1,0,0,1,0,0,0,0,1,0,1,0,0,1,1,0,1,1,0,1,1},
    {1,1,0,0,0,0,1,1,1,0,0,0,0,1,1,0,0,1,0,0,0,0,1,0,1,0,0,0,1,0,1,1,1,1,1}
};

//5x3
std::vector<std::vector<int>> arrow_s_in_border = 
{
    {1,0,0},
    {0,1,0},
    {0,0,1},
    {0,1,0},
    {1,0,0}
};

// 7x4
std::vector<std::vector<int>> arrow_s = 
{
	{1,0,0,0},
	{0,1,0,0},
	{0,0,1,0},
	{0,0,0,1},
	{0,0,1,0},
	{0,1,0,0},
	{1,0,0,0}
};

//7x14
std::vector<std::vector<int>> lightning = {
	{1,0,0,0,0,0,1,0,0,0,0,0,0,0},
	{1,1,0,0,0,0,1,1,1,0,0,0,0,0},
	{0,1,1,1,0,0,1,1,1,1,0,0,0,0},
	{0,0,1,1,1,1,1,1,1,1,1,0,0,0},
	{0,0,0,1,1,1,1,0,0,1,1,1,0,0},
	{0,0,0,0,1,1,1,0,0,0,1,1,1,0},
	{0,0,0,0,0,0,1,0,0,0,0,0,1,1},
};

// 7x64
std::vector<std::vector<int>> excmark = 
{
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,1,1,1,1,1,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,1,1,1,1,1,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,1,1,1,1,1,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0}
};

// 7x20
std::vector<std::vector<int>> hourglass = 
{
	{1,1,1,1,1,1,0,0,0,0,0,0,0,0,1,1,1,1,1,1},
	{1,0,1,0,0,0,1,1,0,0,0,0,1,1,0,0,0,1,0,1},
	{1,0,1,0,0,0,0,0,1,1,1,1,0,0,0,0,0,1,0,1},
	{1,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,1},
	{1,0,1,0,0,0,0,0,1,1,1,1,0,0,0,0,0,1,0,1},
	{1,0,1,0,0,0,1,1,0,0,0,0,1,1,0,0,0,1,0,1},
	{1,1,1,1,1,1,0,0,0,0,0,0,0,0,1,1,1,1,1,1}
};
// 5x14
std::vector<std::vector<int>> hourglass_anim_start =
{
	{0,0,0,1,1,0,0,0,0,1,1,0,1,0},
	{1,0,0,0,0,1,1,1,1,1,0,1,0,0},
	{0,1,0,1,0,0,1,0,1,0,1,0,1,0},
	{1,0,0,0,0,1,1,1,1,1,0,1,0,0},
	{0,0,0,1,1,0,0,0,0,1,1,0,1,0}
};
std::vector<std::vector<int>> hourglass_anim_phase_first = 
{
	{1,0,0,1,1,0,0,0,0,1,1,1,0,0},
	{0,1,0,0,0,1,1,1,1,0,1,0,0,0},
	{1,0,1,0,1,0,0,1,0,1,0,1,0,0},
	{0,1,0,0,0,1,1,1,1,0,1,0,0,0},
	{1,0,0,1,1,0,0,0,0,1,1,1,0,0}
};
std::vector<std::vector<int>> hourglass_anim_phase_second =
{
	{1,0,1,1,1,0,0,0,0,1,1,0,0,0},
	{0,1,0,0,0,1,1,1,1,1,0,0,0,0},
	{1,0,1,0,1,0,1,0,1,0,1,0,0,0},
	{0,1,0,0,0,1,1,1,1,1,0,0,0,0},
	{1,0,1,1,1,0,0,0,0,1,1,0,0,0}
};
std::vector<std::vector<int>> hourglass_anim_phase_third =
{
    {1,0,1,1,1,0,0,0,0,1,1,0,0,0},
    {0,1,0,1,0,1,1,1,1,0,0,0,0,0},
    {1,0,1,0,0,1,0,1,0,1,0,0,0,0},
    {0,1,0,1,0,1,1,1,1,0,0,0,0,0},
    {1,0,1,1,1,0,0,0,0,1,1,0,0,0}
};
std::vector<std::vector<int>> hourglass_anim_phase_last =
{
    {1,0,1,1,1,0,0,0,0,1,1,0,0,0},
    {0,1,0,1,0,1,1,1,1,0,0,0,0,0},
    {1,0,1,0,1,0,1,0,1,0,0,0,0,0},
    {0,1,0,1,0,1,1,1,1,0,0,0,0,0},
    {1,0,1,1,1,0,0,0,0,1,1,0,0,0}
};

void anim_StationReserved()
{
	PatternAnimator p10(&dmd);

    int msdelay = 1000;
    int ROW_START = 4;
    int COL_START = 43;
    int PATTERN_ROW_MAX = 7;
    int PATTERN_COL_MAX = 20;

    // hourglass frame
    p10.draw_pattern_static(hourglass, ROW_START, COL_START, PATTERN_ROW_MAX, PATTERN_COL_MAX);
    // animation loop
    while(true)
    {
        ROW_START = 5;
        COL_START = 40;
        PATTERN_ROW_MAX = 5;
        PATTERN_COL_MAX = 14;
        p10.draw_pattern_static(hourglass_anim_start, ROW_START, COL_START, PATTERN_ROW_MAX, PATTERN_COL_MAX);
        delay(msdelay);
        p10.delete_pattern_static(ROW_START, COL_START, PATTERN_ROW_MAX, PATTERN_COL_MAX);
        p10.draw_pattern_static(hourglass_anim_phase_first, ROW_START, COL_START, PATTERN_ROW_MAX, PATTERN_COL_MAX);
        delay(msdelay);
        p10.delete_pattern_static(ROW_START, COL_START, PATTERN_ROW_MAX, PATTERN_COL_MAX);
        p10.draw_pattern_static(hourglass_anim_phase_second, ROW_START, COL_START, PATTERN_ROW_MAX, PATTERN_COL_MAX);
        delay(msdelay);
        p10.delete_pattern_static(ROW_START, COL_START, PATTERN_ROW_MAX, PATTERN_COL_MAX);
        p10.draw_pattern_static(hourglass_anim_phase_third, ROW_START, COL_START, PATTERN_ROW_MAX, PATTERN_COL_MAX);
        delay(msdelay);
        p10.delete_pattern_static(ROW_START, COL_START, PATTERN_ROW_MAX, PATTERN_COL_MAX);
        p10.draw_pattern_static(hourglass_anim_phase_last, ROW_START, COL_START, PATTERN_ROW_MAX, PATTERN_COL_MAX);
        delay(msdelay);
    }
}
/*--------------------------------------------------------------------------------------
  loop
  Arduino architecture main loop
  --------------------------------------------------------------------------------------*/
void loop(void)
{
	timerWrite(timer, 0); //reset timer (feed watchdog)
	byte b;

	// 10 x 14 font clock, including demo of OR and NOR modes for pixels so that the flashing colon can be overlayed

	dmd.clearScreen( true );
	dmd.selectFont(System5x7);

	// dmd.drawBox(  0,  4, (32*DISPLAYS_ACROSS)-1, (11*DISPLAYS_DOWN)-1, GRAPHICS_NORMAL );
	// delay( 1000 );

	// dmd.drawFilledBox(  0,  4, (32*DISPLAYS_ACROSS)-1, (11*DISPLAYS_DOWN)-1, GRAPHICS_NORMAL );

	// anim_StationReserved();
    PatternAnimator p10(&dmd);

    int ROW_START = 4;
    int COL_START = 63;
    int PATTERN_ROW_MAX = 7;
    int PATTERN_COL_MAX = 35;
    int pxjmp_step = 0;

    // hourglass frame
    p10.draw_pattern_tetris(xsarj, ROW_START, COL_START, PATTERN_ROW_MAX, PATTERN_COL_MAX, pxjmp_step);


	

	//   p10.draw_pattern_blinking(excmark, ROW_START, COL_START, PATTERN_ROW_MAX, PATTERN_COL_MAX, msdelay, cycle);
	//   delay(2000);

	//   PATTERN_ROW_MAX = 7;
	//   PATTERN_COL_MAX = 4;
	//   cycle = 3;


	//   p10.draw_pattern_scrolling(arrow_s, ROW_START, COL_START, PATTERN_ROW_MAX, PATTERN_COL_MAX, pxjmp_step, cycle);
	//   delay(2000);

	delay(3600000);

	serial2_get_data();
}
