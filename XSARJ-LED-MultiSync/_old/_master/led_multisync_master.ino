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
#include <bitset>
#include <cstring>
#include <ArduinoJson.h>

#define HOST_OF_OTA "http://panel.xsarj.com:8081/web/content/2568?download=true"
HTTPClient client;
// Global variables
int totalLength;       // total size of firmware
int currentLength = 0; // current size of written firmware
int version = 0;
int camera_version = 0;
int http_get_version = 9999;

const char* host = "esp32";
constexpr char* ssid = "ARTINSYSTEMS";
constexpr char* password = "Artin2023Artin";
// constexpr char *ssid = "SL-MOBILE";
// constexpr char *password = "sword1998";

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
hw_timer_t* timer = NULL;

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

// #define MAX_ROW 8

/*-------------------------------------------------------------------------------------
ESP NOW
---------------------------------------------------------------------------------------*/
// Structure example to receive data
// Must match the sender structure

// REPLACE WITH YOUR RECEIVER MAC Address
// uint8_t broadcastAddress_1[6] = {0xB0, 0xA7, 0x32, 0xDB, 0xC5, 0x3C};
uint8_t broadcastAddress_1[6] = {0x48, 0xE7, 0x29, 0xB7, 0xE1, 0xCC};
uint8_t broadcastAddress_2[6] = {0x78, 0x21, 0x84, 0xBB, 0x9F, 0x18};
uint8_t broadcastAddress_3[6] = {0x40, 0x22, 0xD8, 0x6E, 0x7F, 0xCC};

bool DEBUG = true;

struct CompareOrder
{
    bool ascending;
    explicit CompareOrder(bool asc = true) : ascending(asc) {
    }
    bool operator()(const std::tuple<const uint8_t*, int>& a, const std::tuple<const uint8_t*, int>& b) const {
        // Compare based on the order value
        if (ascending)
            return std::get<1>(a) < std::get<1>(b); // Ascending order
        else
            return std::get<1>(a) > std::get<1>(b); // Descending order
    }
};

class UniqueQueue {
    std::priority_queue<std::tuple<const uint8_t*, int>, std::vector<std::tuple<const uint8_t*, int>>, CompareOrder> pqueue{};
    std::set<std::tuple<const uint8_t*, int>> proxy{};

public:
    UniqueQueue(bool ascending = true) : pqueue(CompareOrder(ascending)) {
    }
    void push(const std::tuple<const uint8_t*, int>& t) {
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

    std::tuple<const uint8_t*, int> top() {
        return this->pqueue.top();
    }
};

UniqueQueue slave_queue(false);
UniqueQueue proxy_queue(true);
uint8_t copied_mac[6];


enum class Animation
{
    ANIM1,
    ANIM2,
    ANIM3
};

// Send

enum class Flags : unsigned int
{
    None = 0,
    Init = 1 << 0,  // 0001
    Shift = 1 << 1, // 0010
    Flag3 = 1 << 2, // 0100
    Flag4 = 1 << 3  // 1000
};
typedef struct struct_message_to_send
{
    // Animation anim;
    char charArray[64];
    std::bitset<8> flags;
    char bChar[64];
    // 0000 0001 : Draw Pattern Static
    // 0000 0010 : Scrolling Marquee
    // int delay;
    // Flags slave_flag = Flags::None;

} struct_message_to_send;

// Create a struct_message called MasterData
struct_message_to_send message_to_send;
std::vector<std::vector<int>> self_anim_part;


esp_now_peer_info_t peerInfo;

// callback when data is sent
void OnDataSent(const uint8_t* mac_addr, esp_now_send_status_t status) {
    if (DEBUG) {
        Serial.print("\r\nLast Packet Send Status:\t");
        Serial.println(status == ESP_NOW_SEND_SUCCESS ? "Delivery Success" : "Delivery Fail");
        char macStr[18];
        Serial.print("Packet to: ");
        // Copies the sender mac address to a string
        snprintf(macStr, sizeof(macStr), "%02x:%02x:%02x:%02x:%02x:%02x", mac_addr[0], mac_addr[1], mac_addr[2], mac_addr[3], mac_addr[4], mac_addr[5]);
        Serial.print(macStr);
        Serial.print(" send status:\t");
    }
    // Serial.println(status == ESP_NOW_SEND_SUCCESS ? "Delivery Success" : "Delivery Fail");
    // Serial.println(sizeof(message_to_send.anim));
}

// Receive
typedef struct struct_message_to_receive
{
    bool is_anim_completed;
} struct_message_to_receive;

// Create a struct_message called message_to_rcv
struct_message_to_receive message_to_rcv;

bool should_animate = false;
bool sync_mutex = false;

// callback function that will be executed when data is received
void OnDataRecv(const uint8_t* mac, const uint8_t* incomingData, int len) {
    // Serial.println((uintptr_t)mac, HEX);
    memcpy(&message_to_rcv, incomingData, sizeof(message_to_rcv));

    Serial.print("Bytes received: ");
    Serial.println(len);
    sync_mutex = true;
    // try {
    //     char macStr[18];
    //     // Serial.print("Mac received:");
    //     // const uint8_t *t = std::get<0>(slave_queue.top());
    //     snprintf(macStr, sizeof(macStr), "%02x:%02x:%02x:%02x:%02x:%02x", t[0], t[1], t[2], t[3], t[4], t[5]);
    //     Serial.print(macStr);
    // } catch (const std::exception &e) {
    //     Serial.println(e.what());
    //     // std::cerr << e.what() << '\n';
    // }

    Serial.println();
}

/*--------------------------------------------------------------------------------------
  Interrupt handler for Timer1 (TimerOne) driven DMD refresh scanning, this gets
  called at the period set in Timer1.initialize();
  --------------------------------------------------------------------------------------*/
void IRAM_ATTR triggerScan() {
    dmd.scanDisplayBySPI();
}


void anim_StationReserved(PatternAnimator& p10, double cycle = std::numeric_limits<double>::infinity()) {
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


void anim_StationWaiting(PatternAnimator& p10, double cycle = std::numeric_limits<double>::infinity()) {
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


void anim_StationError(PatternAnimator& p10, double cycle = std::numeric_limits<double>::infinity()) {
    int ROW_START = 4;
    int COL_START = 0;
    int msdelay = 0;
    int delaystep = 0;

    // lambda functions for the threads
    auto parallel_drawer_chargehandle = [](PatternAnimator& p10, int msdelay, double cycle) -> void {
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

    auto parallel_drawer_cable = [](PatternAnimator& p10, int msdelay, double cycle) -> void {
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

    auto parallel_drawer_excmark = [](PatternAnimator& p10, int msdelay, double cycle) -> void {
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


void anim_InsertSocket(PatternAnimator& p10, double cycle = std::numeric_limits<double>::infinity()) {
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


void anim_StationCharge_Charging(PatternAnimator& p10, double cycle = std::numeric_limits<double>::infinity()) {
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


void anim_StationWaiting_custom(PatternAnimator& p10, const char* bChars, byte length) {
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

void anim_drawMarquee(const char* bChars, byte length) {
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

    // std::copy(mac, mac + 6, copied_mac);
    // std::tuple<uint8_t *, int> peer{copied_mac, message_to_rcv.order};
    // slave_queue.push(peer);

    memcpy(peerInfo.peer_addr, broadcastAddress_1, 6);
    if (esp_now_add_peer(&peerInfo) != ESP_OK) {
        Serial.println("Failed to add peer");
        return;
    }
    memcpy(peerInfo.peer_addr, broadcastAddress_2, 6);
    if (esp_now_add_peer(&peerInfo) != ESP_OK) {
        Serial.println("Failed to add peer");
        return;
    }
    memcpy(peerInfo.peer_addr, broadcastAddress_3, 6);
    if (esp_now_add_peer(&peerInfo) != ESP_OK) {
        Serial.println("Failed to add peer");
        return;
    }
    Serial.println("All peers registered successfully");
    slave_queue.push(std::make_tuple(broadcastAddress_1, 1));
    slave_queue.push(std::make_tuple(broadcastAddress_2, 2));
    slave_queue.push(std::make_tuple(broadcastAddress_3, 3));
}

void connect_cloud() {
    const char* server_endpoint = "https://panel.xsarj.com/led/subscribe_master";

    // Serialize JSON document
    JsonDocument doc;
    doc["master_mac"] = WiFi.macAddress();
    doc["led_count"] = slave_queue.size() + 1;

    std::string json;
    serializeJson(doc, json);

    HTTPClient http;
    // Send request
    http.begin(server_endpoint);
    http.addHeader("Content-Type", "application/json");
    http.addHeader("Connection", "keep-alive");
    http.addHeader("Accept-Encoding", "gzip, deflate, br");
    http.addHeader("Accept", "*/*");
    http.addHeader("User-Agent", "PostmanRuntime/7.26.8");
    http.setConnectTimeout(5000);
    http.POST(json.c_str());

    // Read response
    Serial.print(http.getString());

    // Disconnect
    http.end();
}

/*--------------------------------------------------------------------------------------
  setup
  Called by the Arduino architecture before the main loop begins
  --------------------------------------------------------------------------------------*/
PatternAnimator p10(&dmd);

void setup(void) {
    Serial.begin(115200);
    Serial2.begin(9600);

    constexpr bool MASTER = true;
    constexpr bool SLAVE = true;

    if (MASTER) {
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


        register_peers();
        connect_cloud();
    } else if (SLAVE) {
        ;
    }

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


    // message_to_send.bitString = ;
    // strcpy(message_to_send.bitString, vectorToBitString(p10.grid));

    // char *bitString = vectorToBitString(grid);
    // std::string bitString = convertToBitString(p10.grid);
    // std::string compressedString = compressBitString(bitString);

    // for (size_t i = 0; i < compressedString.size(); ++i) {
    //     message_to_send.charArray[i] = compressedString[i];
    // }

    // if (DEBUG) {
    //     Serial.print("Bit String: ");
    //     Serial.println(bitString.c_str());
    //     Serial.print("Compressed String: ");
    //     Serial.println();
    //     for (unsigned char c : message_to_send.charArray) {
    //         Serial.print(binaryString(c).c_str());
    //         Serial.println();
    //     }

    //     Serial.println(bitString.size());
    //     Serial.println(compressedString.size());
    // }
}

void prepare_next_matrix(std::vector<std::vector<int>>& matrix) {
    std::string bitString = convertToBitString(matrix);
    std::string compressedString = compressBitString(bitString);

    size_t compressedSize = compressedString.size();
    // Serial.println(compressedSize);
    for (size_t i = 0; i < compressedSize; ++i) {
        message_to_send.charArray[i] = compressedString[i];
    }
}

void prepare_and_shift_next_matrix(std::vector<std::vector<int>>& matrix, std::function<void(std::vector<std::vector<int>>&)> shifter, bool should_print = false) {

    shifter(matrix);

    std::string bitString = convertToBitString(matrix);
    std::string compressedString = compressBitString(bitString);

    size_t compressedSize = compressedString.size();
    // Serial.println(compressedSize);
    for (size_t i = 0; i < compressedSize; ++i) {
        message_to_send.charArray[i] = compressedString[i];
    }

    if (should_print) {
        Serial.println(bitString.c_str());
        Serial.print("Compressed String: ");
        Serial.println();
        for (unsigned char c : message_to_send.charArray) {
            Serial.print(binaryString(c).c_str());
            Serial.println();
        }
    }
}

void shift_matrix_down(std::vector<std::vector<int>>& matrix) {
    int numRows = matrix.size();
    int numCols = matrix[0].size();

    // Save the last row
    std::vector<int> lastRow = matrix[numRows - 1];

    // Shift each row down by one position
    for (int i = numRows - 1; i > 0; --i) {
        matrix[i] = matrix[i - 1];
    }

    // Place the last row at the top
    matrix[0] = lastRow;
}

void shift_matrix_up(std::vector<std::vector<int>>& matrix) {
    int numRows = matrix.size();
    int numCols = matrix[0].size();

    // Save the first row
    std::vector<int> firstRow = matrix[0];

    // Shift each row up by one position
    for (int i = 0; i < numRows - 1; ++i) {
        matrix[i] = matrix[i + 1];
    }

    // Place the first row at the bottom
    matrix[numRows - 1] = firstRow;
}


// Function to convert 2D vector to a bit string
std::string convertToBitString(const std::vector<std::vector<int>>& grid) {
    std::string bitString;
    for (const auto& row : grid) {
        for (int cell : row) {
            bitString += (cell == 1) ? '1' : '0';
        }
    }
    return bitString;
}


// Function to compress the bit string into bit fields
std::string compressBitString(const std::string& bitString) {
    std::string compressedString;
    for (size_t i = 0; i < bitString.size(); i += 8) {
        std::bitset<8> bits(bitString.substr(i, 8));
        compressedString += static_cast<char>(bits.to_ulong());
    }
    return compressedString;
}


// Function to convert bit string back into 2D vector
std::vector<std::vector<int>> convertFromBitString(const std::string& bitString, int numRows, int numCols) {
    std::vector<std::vector<int>> grid(numRows, std::vector<int>(numCols));
    int index = 0;
    for (int i = 0; i < numRows; ++i) {
        for (int j = 0; j < numCols; ++j) {
            grid[i][j] = (bitString[index++] == '1') ? 1 : 0;
        }
    }
    return grid;
}


// Function to decompress the compressed string back into bit string
std::string decompressBitString(const std::string& compressedString) {
    std::string bitString;
    for (unsigned char c : compressedString) {
        std::bitset<8> bits(c);
        bitString += bits.to_string();
    }
    return bitString;
}


// Function to print binary representation of a character
std::string binaryString(unsigned char c) {
    std::string result;
    for (int i = 7; i >= 0; --i) {
        result += ((c >> i) & 1) ? '1' : '0';
    }
    return result;
}


void shift_matrix_diagonal_once(std::vector<std::vector<int>>& grid) {
    int numRows = grid.size();
    int numCols = grid[0].size();

    std::vector<std::vector<int>> temp(numRows, std::vector<int>(numCols, 0));

    for (int i = 0; i < numRows; ++i) {
        for (int j = 0; j < numCols; ++j) {
            int new_i = (i + 1) % numRows;
            int new_j = (j + 1) % numCols;
            temp[new_i][new_j] = grid[i][j];
        }
    }
    grid = temp;
}

void shift_matrix_diagonal_decaying(std::vector<std::vector<int>>& grid) {
    int numRows = grid.size();
    int numCols = grid[0].size();

    // Shift each row down by one and each column to the right by one
    for (int i = numRows - 1; i >= 1; --i) {
        for (int j = numCols - 1; j >= 1; --j) {
            grid[i][j] = grid[i - 1][j - 1];
        }
    }

    // Clear the first row and first column
    for (int i = 0; i < numRows; ++i) {
        grid[i][0] = 0;
    }
    for (int j = 0; j < numCols; ++j) {
        grid[0][j] = 0;
    }
}

void shift_matrix_diagonal_decaying_upwards(std::vector<std::vector<int>>& grid) {
    int numRows = grid.size();
    int numCols = grid[0].size();

    // Shift each row up by one and each column to the right by one
    for (int i = 0; i < numRows - 1; ++i) {
        for (int j = numCols - 1; j >= 1; --j) {
            grid[i][j] = grid[i + 1][j - 1];
        }
    }

    // Clear the first column, except for the first row
    for (int i = 1; i < numRows; ++i) {
        grid[i][0] = 0;
    }

    // Clear the last row
    for (int j = 0; j < numCols; ++j) {
        grid[numRows - 1][j] = 0;
    }
}

void shift_matrix_right(std::vector<std::vector<int>>& grid) {
    int size = grid.size();
    for (int i = 0; i < size; ++i) {
        int temp = grid[i][size - 1];
        for (int j = size - 1; j > 0; --j) {
            grid[i][j] = grid[i][j - 1];
        }
        grid[i][0] = temp;
    }
}


void multianim_horizontal_shift() {
    constexpr int ANIM_DELAY = 20; // 20
    constexpr int SWITCH_DELAY = ANIM_DELAY * 4;
    bool flip = false;

    message_to_send.flags.set(0);

    // Animate Self
    std::vector<std::vector<int>> temp = p10.grid;
    p10.draw_pattern_static(temp, 4, 0);
    delay(ANIM_DELAY);
    for (int i = 0; i < 7; i++) {
        shift_matrix_down(temp);
        p10.draw_pattern_static(temp, 4, 0);
        delay(ANIM_DELAY);
    }
    p10.draw_pattern_static(p10.grid_turned_off, 4, 0);
    delay(SWITCH_DELAY);

    // Animate Slaves
    while (!slave_queue.empty()) {
        std::vector<std::vector<int>> temp = p10.grid;

        prepare_next_matrix(temp);
        esp_err_t result = esp_now_send(std::get<0>(slave_queue.top()), (uint8_t*)&message_to_send, sizeof(message_to_send));
        delay(ANIM_DELAY);

        for (int i = 0; i < 7; i++) {
            prepare_and_shift_next_matrix(temp, shift_matrix_down);
            result = esp_now_send(std::get<0>(slave_queue.top()), (uint8_t*)&message_to_send, sizeof(message_to_send));
            // delete[] message_to_send.bitString;
            delay(ANIM_DELAY);
        }
        // Clear the slave's screen
        prepare_next_matrix(p10.grid_turned_off);
        result = esp_now_send(std::get<0>(slave_queue.top()), (uint8_t*)&message_to_send, sizeof(message_to_send));

        proxy_queue.push(slave_queue.top());
        slave_queue.pop();

        delay(SWITCH_DELAY);
    }
    delay(SWITCH_DELAY * 2);
    temp = p10.grid;
    prepare_and_shift_next_matrix(temp, shift_matrix_up); // 000....1 , last column on
    while (!proxy_queue.empty()) {
        esp_err_t result = esp_now_send(std::get<0>(proxy_queue.top()), (uint8_t*)&message_to_send, sizeof(message_to_send));
        delay(ANIM_DELAY);

        for (int i = 0; i < 7; i++) {
            prepare_and_shift_next_matrix(temp, shift_matrix_up);
            result = esp_now_send(std::get<0>(proxy_queue.top()), (uint8_t*)&message_to_send, sizeof(message_to_send));
            delay(ANIM_DELAY);
        }
        // Clear the slave's screen
        prepare_next_matrix(p10.grid_turned_off);
        result = esp_now_send(std::get<0>(proxy_queue.top()), (uint8_t*)&message_to_send, sizeof(message_to_send));

        slave_queue.push(proxy_queue.top());
        proxy_queue.pop();

        prepare_and_shift_next_matrix(temp, shift_matrix_up); // 000....1 , last column on
        delay(SWITCH_DELAY);
    }
    // Animate Self
    p10.draw_pattern_static(temp, 4, 0);
    delay(ANIM_DELAY);
    for (int i = 0; i < 7; i++) {
        shift_matrix_up(temp);
        p10.draw_pattern_static(temp, 4, 0);
        delay(ANIM_DELAY);
    }
    p10.draw_pattern_static(p10.grid_turned_off, 4, 0);
    delay(SWITCH_DELAY * 2);
}


void multianim_diagonal_shift() {
    constexpr int ANIM_DELAY = 50; // 20
    constexpr int SWITCH_DELAY = ANIM_DELAY * 4;
    constexpr size_t MAX_ROW = 32;
    bool flip = false;
    // p10.draw_pattern_static(p10.grid, 4, 0);
    // delay(1);
    message_to_send.flags.set(0);

    std::vector<std::vector<int>> grid = p10.square_32;
    for (size_t i = 0; i < MAX_ROW + 1; i++) {
        std::vector<std::vector<int>> self_anim_part;
        auto end_iterator = grid.begin() + 8;
        for (auto it = grid.begin(); it != end_iterator; ++it) {
            self_anim_part.push_back(*it);
        }
        p10.draw_pattern_static(self_anim_part, 4, 0);
        // delay(ANIM_DELAY);
        int count = 2;
        // Serial.println(slave_queue.size());
        while (!slave_queue.empty()) {
            std::vector<std::vector<int>> slave_anim_part;
            auto end_iterator = grid.begin() + (8 * count);
            for (auto it = grid.begin() + (8 * (count - 1)); it != end_iterator; ++it) {
                slave_anim_part.push_back(*it);
            }
            prepare_next_matrix(slave_anim_part);

            ++count;

            esp_err_t result = esp_now_send(std::get<0>(slave_queue.top()), (uint8_t*)&message_to_send, sizeof(message_to_send));

            proxy_queue.push(slave_queue.top());
            slave_queue.pop();
        }
        while (!proxy_queue.empty()) {
            slave_queue.push(proxy_queue.top());
            proxy_queue.pop();
        }
        shift_matrix_diagonal_decaying(grid);
        delay(ANIM_DELAY);
    }
    delay(ANIM_DELAY * 4);
}


void multianim_diagonal_shift_fold() {
    constexpr int ANIM_DELAY = 50;
    constexpr int SWITCH_DELAY = ANIM_DELAY * 4;
    constexpr size_t MAX_ROW = 32;
    bool flip = false;
    bool fold = true;
    int shape_length = 4;

    std::vector<std::vector<int>> grid = p10.square_32;

    message_to_send.flags.set(0);

    for (size_t i = 0; i < MAX_ROW - shape_length; ++i) {
        // Animate Self
        std::vector<std::vector<int>> self_anim_part;
        auto end_iterator = grid.begin() + 8;
        for (auto it = grid.begin(); it != end_iterator; ++it) {
            self_anim_part.push_back(*it);
        }
        p10.draw_pattern_static(self_anim_part, 4, 0);
        int count = 2;
        // std::cout << "Queue Size: " << slave_queue.size() << "\n";

        // Animate Slaves
        while (!slave_queue.empty()) {
            std::vector<std::vector<int>> slave_anim_part;
            auto end_iterator = grid.begin() + (8 * count);
            for (auto it = grid.begin() + (8 * (count - 1)); it != end_iterator; ++it) {
                slave_anim_part.push_back(*it);
            }
            prepare_next_matrix(slave_anim_part);

            ++count;

            esp_err_t result = esp_now_send(std::get<0>(slave_queue.top()), (uint8_t*)&message_to_send, sizeof(message_to_send));

            proxy_queue.push(slave_queue.top());
            slave_queue.pop();
        }
        while (!proxy_queue.empty()) {
            slave_queue.push(proxy_queue.top());
            proxy_queue.pop();
        }
        shift_matrix_diagonal_decaying(grid);
        delay(ANIM_DELAY);
    }

    while (!slave_queue.empty()) {
        proxy_queue.push(slave_queue.top());
        slave_queue.pop();
    }

    delay(ANIM_DELAY);

    // Fold to reverse direction
    for (size_t i = 0; i < MAX_ROW + 1; ++i) {
        int count = 4;
        while (!proxy_queue.empty()) {
            std::vector<std::vector<int>> slave_anim_part;
            auto end_iterator = grid.begin() + (8 * count);
            for (auto it = grid.begin() + (8 * (count - 1)); it != end_iterator; ++it) {
                slave_anim_part.push_back(*it);
            }
            prepare_next_matrix(slave_anim_part);

            --count;

            esp_err_t result = esp_now_send(std::get<0>(proxy_queue.top()), (uint8_t*)&message_to_send, sizeof(message_to_send));

            slave_queue.push(proxy_queue.top());
            proxy_queue.pop();
        }
        while (!slave_queue.empty()) {
            proxy_queue.push(slave_queue.top());
            slave_queue.pop();
        }
        // Animate Self
        std::vector<std::vector<int>> self_anim_part;
        auto end_iterator = grid.begin() + 8;
        for (auto it = grid.begin(); it != end_iterator; ++it) {
            self_anim_part.push_back(*it);
        }
        p10.draw_pattern_static(self_anim_part, 4, 0);

        shift_matrix_diagonal_decaying_upwards(grid);
        delay(ANIM_DELAY);
    }
}

void multianim_scrolling_marquee() {
    message_to_send.flags.set(1); // marquee on

    std::vector<const char*> bChars{"Adana", "Istanbul", "Bursa"};

    // Animate Self
    anim_drawMarquee("Antalya", static_cast<byte>(std::strlen("Antalya")));

    while (!slave_queue.empty()) {
        const char* current_bChar = bChars.front();
        strcpy(message_to_send.bChar, current_bChar);
        bChars.erase(bChars.begin());

        Serial.println(message_to_send.bChar);

        esp_err_t result = esp_now_send(std::get<0>(slave_queue.top()), (uint8_t*)&message_to_send, sizeof(message_to_send));

        proxy_queue.push(slave_queue.top());
        slave_queue.pop();
    }
    while (!proxy_queue.empty()) {
        slave_queue.push(proxy_queue.top());
        proxy_queue.pop();
    }
}

/*--------------------------------------------------------------------------------------
  loop
  Arduino architecture main loop
  --------------------------------------------------------------------------------------*/


void loop(void) {
    timerWrite(timer, 0); // reset timer (feed watchdog)

    byte b;
    // 10 x 14 font clock, including demo of OR and NOR modes for pixels so that the flashing colon can be overlayed
    dmd.clearScreen(true);
    dmd.selectFont(System5x7);
    // if (master) {
    // Sync slaves into a queue (ordered based on order values received from slaves)

    // Initial sync to Server


    // Check for context from Server - loop
    //---> Animation Sync
    // multianim_horizontal_shift();
    multianim_diagonal_shift_fold();
    // multianim_scrolling_marquee();
    // multianim_diagonal_shift();
    delay(1);
    // delay(5000);
    // Animate self
    // Serial.println("Master animating...");
    // for (int i = 0; i < MAX_ROW; i++) {
    //     p10.draw_pattern_static(p10.grid, 4, 0);
    //     delay(500);
    //     shift_matrix_down(p10.grid);
    // }
    // dmd.writePixel(4, 0, GRAPHICS_NORMAL, 1);
    // if (flip) {
    //     p10.draw_pattern_static(p10.grid, 4, 0);
    //     delay(2000);
    //     shift_matrix_down(p10.grid);
    //     p10.draw_pattern_static(p10.grid, 4, 0);

    //     flip = false;
    // }

    // dmd.clearScreen(true);
    // Serial.println("Animation completed...");
    // Animate slaves

    // delay(6000);
    // Animate Self/Master


    // delay(SWITCH_DELAY * 2);


    // delay(10000);
    // message_to_send.cmd = false;
    // shift_matrix_down(p10.grid);
    // delay(2000);


    // Heartbeat to slaves
    // } // master
}
