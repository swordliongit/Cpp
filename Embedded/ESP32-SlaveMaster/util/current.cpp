/*
  MASTER
*/

#include <WiFi.h>
#include <algorithm> // for std::sort
#include <array>
#include <esp_now.h>
#include <iostream>
#include <map>
#include <tuple>
#include <vector>


#define RESETPIN 0
// REPLACE WITH YOUR RECEIVER MAC Address
uint8_t broadcastAddress_1[6] = {0xB0, 0xA7, 0x32, 0xDB, 0xC5, 0x3C};
uint8_t broadcastAddress_2[6] = {0x48, 0xE7, 0x29, 0xB7, 0xE1, 0xCC};
uint8_t broadcastAddress_3[6] = {0x78, 0x21, 0x84, 0xBB, 0x9F, 0x18};

int reset_button_esp_value = 0;

// SLAVE 1 : B0:A7:32:DB:C5:3C -> full station
// SLAVE 2 : 48:E7:29:B7:E1:CC
// slave 3 : 78:21:84:BB:9F:18
// std::map<std::string, uint8_t *> slaves{
//     {"Slave 1", broadcastAddress_1},
//     {"Slave 2", broadcastAddress_2},
// };

enum class Animation
{
    ANIM1,
    ANIM2,
    ANIM3
};

std::vector<std::tuple<uint8_t*, Animation>> slaves{
    {broadcastAddress_1, Animation::ANIM1},
    {broadcastAddress_2, Animation::ANIM1},
    {broadcastAddress_3, Animation::ANIM1},
};

// Structure example to send data
// Must match the receiver structure
typedef struct struct_message
{
    Animation anim;
} struct_message;

// Create a struct_message called MasterData
struct_message MasterData;

esp_now_peer_info_t peerInfo;

// callback when data is sent
void OnDataSent(const uint8_t* mac_addr, esp_now_send_status_t status) {
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

void setup() {
    // Init Serial Monitor
    Serial.begin(115200);

    // for boot button
    pinMode(RESETPIN, INPUT_PULLUP);
    pinMode(LED_BUILTIN, OUTPUT);   // blue led on chip to notify boot is pressed
    digitalWrite(LED_BUILTIN, LOW); // start off
    // Set device as a Wi-Fi Station
    WiFi.mode(WIFI_STA);

    // Init ESP-NOW
    if (esp_now_init() != ESP_OK) {
        Serial.println("Error initializing ESP-NOW");
        return;
    }

    // Once ESPNow is successfully Init, we will register for Send CB to
    // get the status of Trasnmitted packet
    esp_now_register_send_cb(OnDataSent);

    // Register peer
    peerInfo.channel = 0;
    peerInfo.encrypt = false;

    // Add peers
    for (auto& [slave, anim] : slaves) {
        memcpy(peerInfo.peer_addr, slave, 6);
        if (esp_now_add_peer(&peerInfo) != ESP_OK) {
            Serial.println("Failed to add peer");
            return;
        }
    }
}

void loop() {
    reset_button_esp_value = digitalRead(RESETPIN); // default : 1

    // Set values to send
    // strcpy(MasterData.a, "Start");
    // MasterData.b = random(1, 20);
    // MasterData.c = 1.2;
    // MasterData.d = true;

    if (reset_button_esp_value == 0) {
        Serial.println("Boot button pressed!");
        digitalWrite(LED_BUILTIN, HIGH);
        for (auto& [slave, anim] : slaves) {
            // Send message via ESP-NOW
            MasterData.anim = anim;
            esp_err_t result = esp_now_send(slave, (uint8_t*)&MasterData, sizeof(MasterData));

            if (result == ESP_OK) {
                Serial.println("Sent with success");
            } else {
                Serial.println("Error sending the data");
            }
            delay(1000);
        }
        digitalWrite(LED_BUILTIN, LOW);
    }
}