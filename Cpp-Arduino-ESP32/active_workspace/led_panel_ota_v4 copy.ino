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
#include <p10_animations_kilicarslan.h>

#include <Arduino.h>
#include <WiFi.h>
#include <EEPROM.h>
#include <Update.h>
#include <HTTPClient.h>

#define HOST_OF_OTA "http://panel.xsarj.com:8081/web/content/2568?download=true"
HTTPClient client;
// Global variables
int totalLength;       //total size of firmware
int currentLength = 0; //current size of written firmware
int version = 0;
int camera_version = 0;
int http_get_version = 9999;

const char* host = "esp32";
char ssid[50] = "arduphone";
char password[50] = "arduphone";

String wifiname = "";
String wifipassword = "";

String wifi_name = "arduphone";
String wifi_password = "arduphone";

int ble_status = 0;
int wifi_status = 0;
int connection_status = 0;
int last_connection_status = 0;
int wifi_strength = 0;
float test_signal_time = 0;

int wifi_name_found = 0;
String timestamp = "0";

int wifi_connected_counter = 0;

unsigned long previousMillis_wifi_timer = 0;
const long interval_wifi_timer = 30000;

String raw_serial2 = "";
String data_from_serial2 = "6";
char screen_test_char[] = "test";
String screen_test_string = "XSarj";


bool charge_started = false;
bool charge_stopped = false;

//TaskHandle_t Task1; -> for esp32 threads

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

  EEPROM.begin(250);
  //testEepromWorking();
  read_Int_Eeprom();
  Serial.println("Eeprom Values Read Succesfully!");

  arrangeWifiAndPassword();
  Serial.print("ssid: ");
  Serial.print(ssid);
  Serial.print(" password: ");
  Serial.print(password);
  Serial.print(" ");

  scan_Wifi();
  if (wifi_name_found == 0) {
    //ble_Setup();
  }

  if (wifi_name_found == 1) {
    tryToReconnectWifi_Setup();
    Serial.print("IP Address: ");
    Serial.println(WiFi.localIP());

    wifi_Http_Get_Request_For_Ota_Filename_Setup();

  }

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
  
  Serial.println("Screen Started");
  Serial.println("Waiting For Serial Datas");
}

void anim_StationReserved(PatternAnimator& p10, double cycle = std::numeric_limits<double>::infinity())
{
  int ROW_START = 4;
  int COL_START = 23;
  int msdelay = 250;

  // hourglass frame
  p10.draw_pattern_static(p10.hourglass, ROW_START, COL_START);
  // animation loop
  // while(cycle > 0)
  // {
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
  // --cycle;
  // }
}

void anim_StationWaiting(PatternAnimator& p10, double cycle = std::numeric_limits<double>::infinity())
{
  int ROW_START = 4;
  int COL_START = 0;
  int PANEL_LAST_COL = 49;
  int msdelay = 4000;
  int delaystep = 25;
  p10.draw_pattern_tetris(p10.xsarj, ROW_START, COL_START, PANEL_LAST_COL, msdelay, cycle);
  dmd.clearScreen(true);
  COL_START = 49;
  p10.draw_pattern_scrolling(p10.xsarj, ROW_START, COL_START, delaystep, cycle);
}

// *********************************
// Station Stopped( chargehandle )
// *********************************

bool animFinished = false;

void parallel_drawer_InsertSocket(PatternAnimator& p10, double cycle)
{
    int ROW_START = 4;
    int COL_START = 0;
    int msdelay = 0;
    int delaystep = 35;
    int COL_FINISH = 25;
    for (int cycle = 0; cycle < 1; ++cycle)
    {
      dmd.drawMarquee("Soketi Takin", 12, (32 * DISPLAYS_ACROSS) - 1, 4);
      long start = millis();
      long timer = start;
      boolean ret = false;
      while (!ret)
      {
        if ((timer + 21) < millis())
        {
          ret = dmd.stepMarquee(-1, 0);
          timer = millis();
        }
      }
    }
}
void parallel_drawer_Barrier(PatternAnimator& p10)
{
  int ROW_START = 4;
  int COL_START = 35;
  
  // 8x28
  std::vector<std::vector<int>> barrier =
  {
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}
  };

  while (!animFinished)
  {
    p10.draw_pattern_static(barrier, ROW_START, COL_START);
  }
  animFinished = false;
  
}

void anim_StationError(PatternAnimator& p10, double cycle = std::numeric_limits<double>::infinity())
{
  int ROW_START = 4;
  int COL_START = 0;
  int msdelay = 0;
  int delaystep = 0;

  // std::ref() must be used if we are passing a reference because thread arguments are moved/copied by value.
  // We can't copy a reference, we can copy the object that it refers to.
  std::thread thread_InsertSocket(parallel_drawer_InsertSocket, std::ref(p10), cycle);
  // std::thread thread_Barrier(parallel_drawer_Barrier, std::ref(p10));

  thread_InsertSocket.join();
  // thread_Barrier.join();
  // thread_BlinkExcmark.join();
}
// *********************************
// *********************************

void anim_StationCharge_Starting()
{
  for (int cycle = 0; cycle < 1; ++cycle)
  {
    dmd.drawMarquee("Sarj Basliyor", 13, (32 * DISPLAYS_ACROSS) - 1, 4);
    long start = millis();
    long timer = start;
    boolean ret = false;
    while (!ret)
    {
      if ((timer + 21) < millis())
      {
        ret = dmd.stepMarquee(-1, 0);
        timer = millis();
      }
    }
  }
}
void anim_StationCharge_Started()
{
  for (int cycle = 0; cycle < 1; ++cycle)
  {
    dmd.drawMarquee("Sarj Basladi", 12, (32 * DISPLAYS_ACROSS) - 1, 4);
    long start = millis();
    long timer = start;
    boolean ret = false;
    while (!ret)
    {
      if ((timer + 21) < millis())
      {
        ret = dmd.stepMarquee(-1, 0);
        timer = millis();
      }
    }
  }
}

void anim_StationCharge_Stopped()
{
  for (int cycle = 0; cycle < 1; ++cycle)
  {
    dmd.drawMarquee("Sarj Sonlandirildi", 18, (32 * DISPLAYS_ACROSS) - 1, 4);
    long start = millis();
    long timer = start;
    boolean ret = false;
    while (!ret)
    {
      if ((timer + 21) < millis())
      {
        ret = dmd.stepMarquee(-1, 0);
        timer = millis();
      }
    }
  }
}

void anim_InsertSocket(PatternAnimator& p10, double cycle = std::numeric_limits<double>::infinity())
{
  for (int cycle = 0; cycle < 1; ++cycle)
  {
    dmd.drawMarquee("Soketi Takin", 12, (32 * DISPLAYS_ACROSS) - 1, 4);
    long start = millis();
    long timer = start;
    boolean ret = false;
    while (!ret)
    {
      if ((timer + 21) < millis())
      {
        ret = dmd.stepMarquee(-1, 0);
        timer = millis();
      }
    }
  }
}

void anim_StationCharge_Charging(PatternAnimator& p10, double cycle = std::numeric_limits<double>::infinity())
{
  int ROW_START = 4;
  int COL_START = 0;
  int delaystep = 35;
  int PATTERN_DISTANCE = 1;

  // // Clear the pattern_pack vector before adding new elements
  // p10.pattern_pack.clear();
  // p10.pattern_pack.push_back(p10.arrow_large);
  // p10.pattern_pack.push_back(p10.arrow_large);
  // p10.pattern_pack.push_back(p10.arrow_large);
  // p10.draw_pattern_scrolling_accumulator_series(p10.pattern_pack, ROW_START, COL_START, PATTERN_DISTANCE, delaystep, cycle);


  p10.draw_pattern_scrolling(p10.lightning, ROW_START, COL_START, delaystep, cycle);
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


PatternAnimator p10(&dmd);

void loop(void)
{
  timerWrite(timer, 0); //reset timer (feed watchdog)

  byte b;
  // 10 x 14 font clock, including demo of OR and NOR modes for pixels so that the flashing colon can be overlayed
  dmd.clearScreen( true );
  dmd.selectFont(System5x7);

  serial2_get_data();

  // test
  // serial2_get_data(p10, dmd, "2");

  // anim_StationError(p10, 1);
  // anim_StationReserved(p10, 1);
  // anim_StationCharging(p10, 1);
  // anim_StationWaiting(p10, 1);

  if (data_from_serial2 == "1")
  {
    charge_started = false;
    charge_stopped = false;
    anim_StationCharge_Starting();

  }
  else if (data_from_serial2 == "2")
  {
    charge_stopped = false;
    if (!charge_started)
    {
      anim_StationCharge_Started();
      charge_started = true;
    }
    anim_StationCharge_Charging(p10, 1);
  }
  else if (data_from_serial2 == "3")
  {
    charge_started = false;
    charge_stopped = false;
    anim_StationError(p10, 1);
  }
  else if (data_from_serial2 == "4")
  {
    charge_started = false;
    if (!charge_stopped)
    {
      anim_StationCharge_Stopped();
      charge_stopped = true;
    }
    anim_StationWaiting(p10, 1);
  }
  else if (data_from_serial2 == "5")
  {
    charge_started = false;
    charge_stopped = false;
    anim_InsertSocket(p10, 1);
    anim_StationError(p10, 1);
  }
  else if (data_from_serial2 == "6")
  {
    charge_started = false;
    charge_stopped = false;
    // anim_StationCharge_Starting();
    anim_StationWaiting(p10, 1);
    // anim_StationError(p10, 1);
    // anim_StationCharge_Charging(p10, 1);
  }
  else if (data_from_serial2 == "7")
  {
    charge_started = false;
    charge_stopped = false;
    anim_StationReserved(p10, 1);
  }
  else if (data_from_serial2 == "8")
  {
    charge_started = false;
    charge_stopped = false;
    anim_InsertSocket(p10, 1);
  }
  else if (data_from_serial2 == "99")
  {
    Serial.println("Esp32 Restarted By Master");
    ESP.restart();

  }

  //wifi_Http_Get_Request_For_Ota_Filename();

}
