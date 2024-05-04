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

#include <Arduino.h>
#include <WiFi.h>
#include <EEPROM.h>
#include <Update.h>
#include <HTTPClient.h>

#include <esp_now.h>
#include <esp_wifi.h>
#include <bitset>

#define HOST_OF_OTA "http://panel.xsarj.com:8081/web/content/2568?download=true"
HTTPClient client;
// Global variables
int totalLength;       // total size of firmware
int currentLength = 0; // current size of written firmware
int version = 0;
int camera_version = 0;
int http_get_version = 9999;

const char *host = "esp32";
// char ssid[50] = "arduphone";
// char password[50] = "arduphone";


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

// Fire up the DMD library as dmd
#define DISPLAYS_ACROSS 2
#define DISPLAYS_DOWN 1
DMD dmd(DISPLAYS_ACROSS, DISPLAYS_DOWN);

#define MAX_ROW 8


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

/*-------------------------------------------------------------------------------------
ESP NOW
---------------------------------------------------------------------------------------*/
// Structure example to receive data
// Must match the sender structure

// REPLACE WITH YOUR RECEIVER MAC Address
// Master: B0:A7:32:DB:C5:3C, 48:E7:29:95:23:34 ( home )
uint8_t broadcastAddress[6] = {0xB0, 0xA7, 0x32, 0xDB, 0xC5, 0x3C};
// uint8_t broadcastAddress[6] = {0x48, 0xE7, 0x29, 0x95, 0x23, 0x34};

enum class Animation
{
    ANIM1,
    ANIM2,
    ANIM3
};
// Send
typedef struct struct_message_to_send
{
    bool is_anim_completed;
} struct_message_to_send;

// Create a struct_message called MasterData
struct_message_to_send message_to_send;

esp_now_peer_info_t peerInfo;

// bool mac_sent = false;

// callback when data is sent
void OnDataSent(const uint8_t *mac_addr, esp_now_send_status_t status) {
    char macStr[18];
    Serial.print("Packet to: ");
    // Copies the sender mac address to a string
    snprintf(macStr, sizeof(macStr), "%02x:%02x:%02x:%02x:%02x:%02x", mac_addr[0], mac_addr[1], mac_addr[2], mac_addr[3], mac_addr[4], mac_addr[5]);
    Serial.print(macStr);
    Serial.print(" send status:\t");
    Serial.println(status == ESP_NOW_SEND_SUCCESS ? "Delivery Success" : "Delivery Fail");

    // Serial.println(status);
    // if (!status)
    //     mac_sent = true;
}

// Receive
typedef struct struct_message_to_receive
{
    char charArray[64];
    size_t bitSetStringSize;
    bool cmd;
    // char t[32];
} struct_message_to_receive;

// Create a struct_message called message_to_rcv
struct_message_to_receive message_to_rcv;

bool should_animate = false;


std::vector<std::vector<int>> self_anim_part;

std::string compressedString;

std::vector<std::vector<int>> convertFromBitString(const std::string &bitString, int numRows, int numCols);

PatternAnimator p10(&dmd);
// std::string decompressedString;
// std::vector<std::vector<int>> reconstructedGrid;
std::vector<std::vector<int>> reconstructedGrid;


// callback function that will be executed when data is received
void OnDataRecv(const uint8_t *mac, const uint8_t *incomingData, int len) {
    memcpy(&message_to_rcv, incomingData, sizeof(message_to_rcv));
    Serial.print("Bytes received: ");
    Serial.println(len);
    for (unsigned char c : message_to_rcv.charArray) {
        Serial.print(binaryString(c).c_str());
        Serial.println();
    }
    Serial.println();
    Serial.println();
    compressedString = std::string(message_to_rcv.charArray, 64);

    std::string decompressedString = decompressBitString(compressedString);
    reconstructedGrid = convertFromBitString(decompressedString, p10.grid.size(), p10.grid[0].size());
    // Serial.print("Char: ");
    // Serial.println(message_to_rcv.t);
    Serial.println();

    should_animate = true;
}

/*--------------------------------------------------------------------------------------
  Interrupt handler for Timer1 (TimerOne) driven DMD refresh scanning, this gets
  called at the period set in Timer1.initialize();
  --------------------------------------------------------------------------------------*/
void IRAM_ATTR triggerScan() {
    dmd.scanDisplayBySPI();
}
// Insert your SSID
constexpr char WIFI_SSID[] = "ARTINSYSTEMS";
// constexpr char WIFI_SSID[] = "SL-MOBILE";

int32_t getWiFiChannel(const char *ssid) {
    if (int32_t n = WiFi.scanNetworks()) {
        for (uint8_t i = 0; i < n; i++) {
            if (!strcmp(ssid, WiFi.SSID(i).c_str())) {
                return WiFi.channel(i);
            }
        }
    }
    return 0;
}

// Function to convert 2D vector to a bit string
std::string convertToBitString(const std::vector<std::vector<int>> &grid) {
    std::string bitString;
    for (const auto &row : grid) {
        for (int cell : row) {
            bitString += (cell == 1) ? '1' : '0';
        }
    }
    return bitString;
}

// Function to compress the bit string into bit fields
std::string compressBitString(const std::string &bitString) {
    std::string compressedString;
    for (size_t i = 0; i < bitString.size(); i += 8) {
        std::bitset<8> bits(bitString.substr(i, 8));
        compressedString += static_cast<char>(bits.to_ulong());
    }
    return compressedString;
}

// Function to convert bit string back into 2D vector
std::vector<std::vector<int>> convertFromBitString(const std::string &bitString, int numRows, int numCols) {
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
std::string decompressBitString(const std::string &compressedString) {
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

/*--------------------------------------------------------------------------------------
  setup
  Called by the Arduino architecture before the main loop begins
  --------------------------------------------------------------------------------------*/
void setup(void) {
    Serial.begin(115200);
    Serial2.begin(9600);

    // Set device as a Wi-Fi Station
    WiFi.mode(WIFI_STA);

    int32_t channel = getWiFiChannel(WIFI_SSID);

    WiFi.printDiag(Serial); // Uncomment to verify channel number before
    esp_wifi_set_promiscuous(true);
    esp_wifi_set_channel(channel, WIFI_SECOND_CHAN_NONE);
    esp_wifi_set_promiscuous(false);
    WiFi.printDiag(Serial); // Uncomment to verify channel change after

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

    // Register peer
    peerInfo.channel = 0;
    peerInfo.encrypt = false;

    memcpy(peerInfo.peer_addr, broadcastAddress, 6);
    if (esp_now_add_peer(&peerInfo) != ESP_OK) {
        Serial.println("Failed to add peer");
        return;
    }
    // Serial2.begin(115200);

    // createSSID();
    // Serial.println("Device Id = " + id);

    // EEPROM.begin(250);
    // testEepromWorking();
    // read_Int_Eeprom();
    // Serial.println("Eeprom Values Read Succesfully!");

    // arrangeWifiAndPassword();
    // Serial.print("ssid: ");
    // Serial.print(ssid);
    // Serial.print(" password: ");
    // Serial.print(password);
    // Serial.print(" ");

    // scan_Wifi();
    // if (wifi_name_found == 0)
    // {
    //     // ble_Setup();
    // }
    /*
      if (wifi_name_found == 1) {
        tryToReconnectWifi_Setup();
        Serial.print("IP Address: ");
        Serial.println(WiFi.localIP());

        //wifi_Http_Get_Request_For_Ota_Filename_Setup();

      }
    */

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

    log_i("Total heap: %u", ESP.getHeapSize());
    log_i("Free heap: %u", ESP.getFreeHeap());
    log_i("Total PSRAM: %u", ESP.getPsramSize());
    log_i("Free PSRAM: %d", ESP.getFreePsram());
    log_i("spiram size %u", esp_spiram_get_size());
    log_i("himem free %u", esp_himem_get_free_size());
    log_i("himem phys %u", esp_himem_get_phys_size());
    log_i("himem reserved %u", esp_himem_reserved_area_size());
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

void shiftMatrixDownOnce(std::vector<std::vector<int>> &matrix) {
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


bool flip = true;

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

    if (should_animate) {
        // Serial.println();
        // Serial.println();

        // draw the pattern

        // p10.draw_pattern_static(p10.grid, 4, 0);
        // shiftMatrixDownOnce(p10.grid);

        // // Check if the reconstruction is correct
        // // for (const auto &row : reconstructedGrid) {
        // //     for (int cell : row) {
        // //         std::cout << cell << " ";
        // //     }
        // //     std::cout << std::endl;
        // // }
        // // Serial.print(decompressedString.c_str());
        // reconstructedGrid.clear();
        p10.draw_pattern_static(reconstructedGrid, 4, 0);
    }

    delay(1);
    // delay(2000);

    // Send Mac to serial
    // while (!mac_sent) {
    //     esp_err_t result = esp_now_send(broadcastAddress, (uint8_t *)&message_to_send, sizeof(message_to_send));

    //     if (result == ESP_OK) {
    //         Serial.println("Sent with success");
    //     } else {
    //         Serial.println("Error sending the data");
    //     }
    //     delay(1000);
    // }

    // if (slave) {
    // Listen for animation command
    // Serial.println("[Slave] Waiting for command from Master...");
    // p10.draw_pattern_static(p10.grid, 12, 0);
    // delay(5000);
    // p10.draw_pattern_static(p10.grid, 4, 0);

    // delay(2000);
    // if (should_animate) {
    //     // digitalWrite(LED_BUILTIN, HIGH);
    //     // Serial.println("Animating...");

    //     if (message_to_rcv.cmd) {
    //         // p10.draw_pattern_static(message_to_rcv.anim, 4, 0);
    //         delay(1);
    //     } else {
    //         dmd.clearScreen(true);
    //     }
    // switch (message_) {
    // case Animation::ANIM1: {
    //     // dmd.writePixel(4, 0, GRAPHICS_NORMAL, 1);
    //     p10.draw_pattern_static(p10.grid, 4, 0);
    // for (int i = 0; i < MAX_ROW; i++) {
    //     p10.draw_pattern_static(p10.grid, 4, 0);
    //     delay(500);
    //     shiftMatrixDownOnce(p10.grid);
    // }
    // dmd.clearScreen(true);
    // Serial.println("Animation completed...");
    // // dmd.clearScreen(true);
    // message_to_send.is_anim_completed = true;
    // esp_err_t result = esp_now_send(broadcastAddress, (uint8_t *)&message_to_send, sizeof(message_to_send));
    // should_animate = false;
    // if (result == ESP_OK) {
    //     Serial.println("Sent with success");
    // } else {
    //     Serial.println("Error sending the data");
    // }
    // break;
}

// default:
//     break;
// }


// should_animate = false;
// digitalWrite(LED_BUILTIN, LOW);
// } slave end