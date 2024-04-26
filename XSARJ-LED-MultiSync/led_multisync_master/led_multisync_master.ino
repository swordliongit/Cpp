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
#include <DMD32.h> //
#include "fonts/SystemFont5x7.h"
#include "fonts/Arial_black_16.h"
#include "fonts/Arial14.h"

#include "p10_animations_kilicarslan.h"

#include <iostream>
#include <vector> // for vector
#include <limits> // for numeric_limits
#include <thread>
#include <tuple>

#include <Arduino.h>
#include <WiFi.h>
#include <EEPROM.h>
#include <Update.h>
#include <HTTPClient.h>

#include <esp_now.h>
#include <queue>
#include <set>
#include <tuple>
#include <string>
#include <esp_wifi.h>
#include <Arduino_JSON.h>

#define HOST_OF_OTA "http://panel.xsarj.com:8081/web/content/2568?download=true"
HTTPClient client;
// Global variables
int totalLength;       // total size of firmware
int currentLength = 0; // current size of written firmware
int version = 0;
int camera_version = 0;
int http_get_version = 9999;

const char *host = "esp32";
// constexpr char *ssid = "ARTINSYSTEMS";
// constexpr char *password = "Artin2023Artin";
constexpr char *ssid = "SL-MOBILE";
constexpr char *password = "sword1998";

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

// TaskHandle_t Task1; -> for esp32 threads

const int wdtTimeout = 60000; // time in ms to trigger the watchdog
hw_timer_t *timer = NULL;

void IRAM_ATTR resetModule() {
    ets_printf("reboot\n");
    esp_restart();
}

char uniquename[15]; // Create a Unique AP from MAC address
char uniqueid[15];
String id;

// Fire up the DMD library as dmd
#define DISPLAYS_ACROSS 2
#define DISPLAYS_DOWN 1
DMD dmd(DISPLAYS_ACROSS, DISPLAYS_DOWN);

/*-------------------------------------------------------------------------------------
ESP NOW
---------------------------------------------------------------------------------------*/
// Structure example to receive data
// Must match the sender structure

// REPLACE WITH YOUR RECEIVER MAC Address
uint8_t broadcastAddress_1[6] = {0xB0, 0xA7, 0x32, 0xDB, 0xC5, 0x3C};
uint8_t broadcastAddress_2[6] = {0x48, 0xE7, 0x29, 0xB7, 0xE1, 0xCC};
uint8_t broadcastAddress_3[6] = {0x78, 0x21, 0x84, 0xBB, 0x9F, 0x18};

struct CompareOrder
{
    bool operator()(const std::tuple<const uint8_t *, int> &a, const std::tuple<const uint8_t *, int> &b) const {
        // Compare based on the order value
        return std::get<1>(a) > std::get<1>(b); // Change > to < for ascending order
    }
};

class UniqueQueue
{
    std::priority_queue<std::tuple<const uint8_t *, int>, std::vector<std::tuple<const uint8_t *, int>>, CompareOrder>
        pqueue{};
    std::set<std::tuple<const uint8_t *, int>> proxy{};

public:
    void push(const std::tuple<const uint8_t *, int> &t) {
        if (this->proxy.insert(t).second) {
            this->pqueue.push(t);
        }
    }

    void pop() {
        this->proxy.erase(pqueue.top());
        this->pqueue.pop();
    }

    size_t size() {
        return this->pqueue.size();
    }

    bool empty() {
        return this->pqueue.empty();
    }

    std::tuple<const uint8_t *, int> top() {
        return this->pqueue.top();
    }
};

UniqueQueue slave_queue;
uint8_t copied_mac[6];


enum class Animation
{
    ANIM1,
    ANIM2,
    ANIM3
};

// std::vector<std::tuple<uint8_t*, Animation>> receivers{
//     {broadcastAddress_1, Animation::ANIM1},
//     {broadcastAddress_2, Animation::ANIM1},
//     {broadcastAddress_3, Animation::ANIM1},
// };

// Send
typedef struct struct_message_to_send
{
    Animation anim;
} struct_message_to_send;

// Create a struct_message called MasterData
struct_message_to_send message_to_send;

esp_now_peer_info_t peerInfo;

// callback when data is sent
void OnDataSent(const uint8_t *mac_addr, esp_now_send_status_t status) {
    // Serial.print("\r\nLast Packet Send Status:\t");
    // Serial.println(status == ESP_NOW_SEND_SUCCESS ? "Delivery Success" : "Delivery Fail");
    char macStr[18];
    Serial.print("Packet to: ");
    // Copies the sender mac address to a string
    snprintf(macStr,
             sizeof(macStr),
             "%02x:%02x:%02x:%02x:%02x:%02x",
             mac_addr[0],
             mac_addr[1],
             mac_addr[2],
             mac_addr[3],
             mac_addr[4],
             mac_addr[5]);
    Serial.print(macStr);
    Serial.print(" send status:\t");
    Serial.println(status == ESP_NOW_SEND_SUCCESS ? "Delivery Success" : "Delivery Fail");
}

// Receive
typedef struct struct_message_to_receive
{
    int order;
} struct_message_to_receive;

// Create a struct_message called message_to_rcv
struct_message_to_receive message_to_rcv;

bool should_animate = false;

// callback function that will be executed when data is received
void OnDataRecv(const uint8_t *mac, const uint8_t *incomingData, int len) {
    // Serial.println((uintptr_t)mac, HEX);
    memcpy(&message_to_rcv, incomingData, sizeof(message_to_rcv));

    std::copy(mac, mac + 6, copied_mac);
    slave_queue.push(std::make_tuple(copied_mac, message_to_rcv.order));

    Serial.print("Bytes received: ");
    Serial.println(len);
    try {
        char macStr[18];
        Serial.print("Mac received:");
        const uint8_t *t = std::get<0>(slave_queue.top());
        snprintf(macStr, sizeof(macStr), "%02x:%02x:%02x:%02x:%02x:%02x", t[0], t[1], t[2], t[3], t[4], t[5]);
        Serial.print(macStr);
    } catch (const std::exception &e) {
        Serial.println(e.what());
        // std::cerr << e.what() << '\n';
    }

    Serial.println();
    Serial.print("Order: ");
    Serial.println(message_to_rcv.order);
    Serial.println();
}

/*--------------------------------------------------------------------------------------
  Interrupt handler for Timer1 (TimerOne) driven DMD refresh scanning, this gets
  called at the period set in Timer1.initialize();
  --------------------------------------------------------------------------------------*/
void IRAM_ATTR triggerScan() {
    dmd.scanDisplayBySPI();
}


void anim_StationReserved(PatternAnimator &p10, double cycle = std::numeric_limits<double>::infinity()) {
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


void anim_StationWaiting(PatternAnimator &p10, double cycle = std::numeric_limits<double>::infinity()) {
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


void anim_StationError(PatternAnimator &p10, double cycle = std::numeric_limits<double>::infinity()) {
    int ROW_START = 4;
    int COL_START = 0;
    int msdelay = 0;
    int delaystep = 0;

    // lambda functions for the threads
    auto parallel_drawer_chargehandle = [](PatternAnimator &p10, int msdelay, double cycle) -> void {
        cycle += 16;
        int ROW_START = 4;
        int COL_START = 41;

        // while(cycle > 0)
        // {
        p10.draw_pattern_static(p10.chargehandle_frame_1, ROW_START, COL_START);
        delay(msdelay);
        p10.draw_pattern_static(p10.chargehandle_frame_2, ROW_START, COL_START);
        delay(msdelay);
        p10.draw_pattern_static(p10.chargehandle_frame_3, ROW_START, COL_START);
        delay(msdelay);
        //     --cycle;
        // }
    };

    auto parallel_drawer_cable = [](PatternAnimator &p10, int msdelay, double cycle) -> void {
        cycle += 6;
        int ROW_START = 4;
        int COL_START = 26;

        // while(cycle > 0)
        // {
        p10.draw_pattern_static(p10.chargehandle_cable_frame_1, ROW_START, COL_START);
        delay(msdelay);
        p10.draw_pattern_static(p10.chargehandle_cable_frame_2, ROW_START, COL_START);
        delay(msdelay);
        //     --cycle;
        // }
    };

    auto parallel_drawer_excmark = [](PatternAnimator &p10, int msdelay, double cycle) -> void {
        int ROW_START = 4;
        int COL_START = 3;

        p10.draw_pattern_blinking(p10.excmark_little, ROW_START, COL_START, msdelay, cycle);
    };

    // std::ref() must be used if we are passing a reference because thread arguments are moved/copied by value.
    // We can't copy a reference, we can copy the object that it refers to.
    msdelay = 40;
    std::thread thread_chargehandle(parallel_drawer_chargehandle, std::ref(p10), msdelay, cycle);

    msdelay = 140;
    std::thread thread_cable(parallel_drawer_cable, std::ref(p10), msdelay, cycle);

    // ROW_START = 4;
    // COL_START = 3;
    msdelay = 200;
    std::thread thread_excmark(parallel_drawer_excmark, std::ref(p10), msdelay, cycle);

    thread_chargehandle.join();
    thread_cable.join();
    thread_excmark.join();
}
// *********************************
// *********************************


void anim_StationCharge_Starting() {
    for (int cycle = 0; cycle < 1; ++cycle) {
        dmd.drawMarquee("Sarj Basliyor", 13, (32 * DISPLAYS_ACROSS) - 1, 4);
        long start = millis();
        long timer = start;
        boolean ret = false;
        while (!ret) {
            if ((timer + 21) < millis()) {
                ret = dmd.stepMarquee(-1, 0);
                timer = millis();
            }
        }
    }
}


void anim_StationCharge_Started() {
    for (int cycle = 0; cycle < 1; ++cycle) {
        dmd.drawMarquee("Sarj Basladi", 12, (32 * DISPLAYS_ACROSS) - 1, 4);
        long start = millis();
        long timer = start;
        boolean ret = false;
        while (!ret) {
            if ((timer + 21) < millis()) {
                ret = dmd.stepMarquee(-1, 0);
                timer = millis();
            }
        }
    }
}


void anim_StationCharge_Stopped() {
    for (int cycle = 0; cycle < 1; ++cycle) {
        dmd.drawMarquee("Sarj Sonlandirildi", 18, (32 * DISPLAYS_ACROSS) - 1, 4);
        long start = millis();
        long timer = start;
        boolean ret = false;
        while (!ret) {
            if ((timer + 21) < millis()) {
                ret = dmd.stepMarquee(-1, 0);
                timer = millis();
            }
        }
    }
}


void anim_InsertSocket(PatternAnimator &p10, double cycle = std::numeric_limits<double>::infinity()) {
    for (int cycle = 0; cycle < 1; ++cycle) {
        dmd.drawMarquee("Soketi Takin", 12, (32 * DISPLAYS_ACROSS) - 1, 4);
        long start = millis();
        long timer = start;
        boolean ret = false;
        while (!ret) {
            if ((timer + 21) < millis()) {
                ret = dmd.stepMarquee(-1, 0);
                timer = millis();
            }
        }
    }
}


void anim_StationCharge_Charging(PatternAnimator &p10, double cycle = std::numeric_limits<double>::infinity()) {
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


void anim_StationWaiting_custom(PatternAnimator &p10, const char *bChars, byte length) {
    dmd.drawMarquee(bChars, length, (32 * DISPLAYS_ACROSS) - 1, 4);
    long start = millis();
    long timer = start;
    boolean ret = false;
    while (!ret) {
        if ((timer + 21) < millis()) {
            ret = dmd.stepMarquee(-1, 0);
            timer = millis();
        }
    }
}


void runthreads() {

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

void register_peers() {
    // Register peer
    peerInfo.channel = 0;
    peerInfo.encrypt = false;

    const uint8_t *t = std::get<0>(slave_queue.top());
    char macStr2[18];
    snprintf(macStr2, sizeof(macStr2), "%02x:%02x:%02x:%02x:%02x:%02x", t[0], t[1], t[2], t[3], t[4], t[5]);
    Serial.print("Mac in register_peers(): ");
    Serial.println(macStr2);
    std::vector<std::tuple<const uint8_t *, int>> popped_list;
    while (!slave_queue.empty()) {

        memcpy(peerInfo.peer_addr, std::get<0>(slave_queue.top()), 6);
        if (esp_now_add_peer(&peerInfo) != ESP_OK) {
            Serial.println("Failed to add peer");
            return;
        }
        popped_list.push_back(slave_queue.top());
        slave_queue.pop();
    }

    for (auto &el : popped_list) {
        slave_queue.push(el);
    }
}

/*--------------------------------------------------------------------------------------
  setup
  Called by the Arduino architecture before the main loop begins
  --------------------------------------------------------------------------------------*/
void setup(void) {
    Serial.begin(115200);
    Serial2.begin(9600);

    // ESP-NOW and WiFi working simultaneously
    // Set device as a Wi-Fi Station
    WiFi.mode(WIFI_AP_STA);
    WiFi.begin(ssid, password);
    // //check wi-fi is connected to wi-fi network
    while (WiFi.status() != WL_CONNECTED) {
        delay(1000);
        Serial.print(".");
    }
    Serial.print("Station IP Address: ");
    Serial.println(WiFi.localIP());
    Serial.print("Wi-Fi Channel: ");
    Serial.println(WiFi.channel());
    Serial.println(WiFi.macAddress());
    // Init ESP-NOW
    if (esp_now_init() != ESP_OK) {
        Serial.println("Error initializing ESP-NOW");
        return;
    }

    // Once ESPNow is successfully Init, we will register for recv CB to
    // get recv packer info
    esp_now_register_recv_cb(OnDataRecv);
    // Once ESPNow is successfully Init, we will register for Send CB to
    // get the status of Trasnmitted packet
    esp_now_register_send_cb(OnDataSent);

    pinMode(LED_BUILTIN, OUTPUT);   // blue led on chip to notify boot is pressed
    digitalWrite(LED_BUILTIN, LOW); // start off

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
    // clear/init the DMD pixels held in RAM
    dmd.clearScreen(true); // true is normal (all pixels off), false is negative (all pixels on)

    Serial.println("Screen Started");
    Serial.println("Waiting For Serial Datas");
}

/*--------------------------------------------------------------------------------------
  loop
  Arduino architecture main loop
  --------------------------------------------------------------------------------------*/

PatternAnimator p10(&dmd);

void loop(void) {
    timerWrite(timer, 0); // reset timer (feed watchdog)

    byte b;
    // 10 x 14 font clock, including demo of OR and NOR modes for pixels so that the flashing colon can be overlayed
    dmd.clearScreen(true);
    dmd.selectFont(System5x7);

    delay(5000);
    // Sync slaves into a queue (ordered based on order values received from slaves)
    if (!slave_queue.empty()) {
        register_peers();
    }
    Serial.print("Queue size: ");
    Serial.println(slave_queue.size());
    // while (!slave_queue.empty()) {
    //     Serial.println(std::get<1>(slave_queue.top()));
    //     slave_queue.pop();
    // }

    // Initial sync to Server


    // Check for context from Server - loop
    //---> Sync slaves for animation
    delay(8000);

    if (!slave_queue.empty()) {
        char macStr[18];
        auto mac_addr = std::get<0>(slave_queue.top());
        snprintf(macStr,
                 sizeof(macStr),
                 "%02x:%02x:%02x:%02x:%02x:%02x",
                 mac_addr[0],
                 mac_addr[1],
                 mac_addr[2],
                 mac_addr[3],
                 mac_addr[4],
                 mac_addr[5]);
        Serial.println(macStr);
    }
    while (!slave_queue.empty()) {
        message_to_send.anim = Animation::ANIM1;
        esp_err_t result =
            esp_now_send(std::get<0>(slave_queue.top()), (uint8_t *)&message_to_send, sizeof(message_to_send));

        if (result == ESP_OK) {
            Serial.println("Sent with success");
        } else {
            Serial.println("Error sending the data");
        }
        delay(1000);
        slave_queue.pop();
    }
    Serial.print("Queue size: ");
    Serial.println(slave_queue.size());

    // Heartbeat to slaves
}
