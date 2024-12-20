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

String data_from_serial2 = "";
char screen_test_char[] = "test";
String screen_test_string = "Xsarj Test";

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
  timerAlarmWrite(timer, wdtTimeout * 1000, false); //set time in us
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
  screen_test_string.toCharArray(screen_test_char, int(screen_test_string.length())+1);
  dmd.drawMarquee(screen_test_char, int(screen_test_string.length()), (32 * DISPLAYS_ACROSS) - 1, 4);
  long start = millis();
  long timer = start;
  boolean ret = false;
  while (!ret) {
    if ((timer + 30) < millis()) {
      ret = dmd.stepMarquee(-1, 0);
      timer = millis();
    }
  }

  serial2_get_data();
}
