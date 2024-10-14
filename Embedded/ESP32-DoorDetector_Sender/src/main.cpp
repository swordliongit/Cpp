/*
 * This ESP32 code is created by esp32io.com
 *
 * This ESP32 code is released in the public domain
 *
 * For more detail (instruction and wiring diagram), visit https://esp32io.com/tutorials/esp32-switch
 */

#include <WiFi.h>
#include <esp_now.h>


#include <esp_wifi.h>
#include <ezButton.h>
ezButton mySwitch(17); // create ezButton object that attach to ESP32 pin GPIO17

uint8_t broadcastAddress_1[6] = {0x48, 0xE7, 0x29, 0x95, 0x23, 0x34};
// 78:21:84:9D:F0:B8
// 0x8C, 0xCE, 0x4E, 0x8C, 0x64, 0x44
// 48:E7:29:95:23:34

// Structure example to send data
// Must match the receiver structure
struct struct_message
{
    char a[32];
    int b;
    float c;
    bool d;
};

// Create a struct_message called myData
struct_message myData;

esp_now_peer_info_t peerInfo;

bool message_sent = false; // Flag to track if the message has been sent

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

int32_t getWiFiChannel(const char* ssid) {
    if (int32_t n = WiFi.scanNetworks()) {
        for (uint8_t i = 0; i < n; i++) {
            if (!strcmp(ssid, WiFi.SSID(i).c_str())) {
                return WiFi.channel(i);
            }
        }
    }
    return 0;
}

void setup() {
    Serial.begin(115200);


    pinMode(LED_BUILTIN, OUTPUT);   // blue led on chip to notify boot is pressed
    digitalWrite(LED_BUILTIN, LOW); // start off
    // switch setup
    mySwitch.setDebounceTime(50); // set debounce time to 50 milliseconds

    // Set device as a Wi-Fi Station
    WiFi.mode(WIFI_STA);
    int32_t channel = getWiFiChannel("SL-HOME");

    if (channel == 0) {
        peerInfo.channel = 0;
    } else {
        WiFi.printDiag(Serial); // Uncomment to verify channel number before
        esp_wifi_set_promiscuous(true);
        esp_wifi_set_channel(channel, WIFI_SECOND_CHAN_NONE);
        esp_wifi_set_promiscuous(false);
        WiFi.printDiag(Serial); // Uncomment to verify channel change after
    }

    // Init ESP-NOW
    if (esp_now_init() != ESP_OK) {
        Serial.println("Error initializing ESP-NOW");
        return;
    }

    // Once ESPNow is successfully Init, we will register for Send CB to
    // get the status of Trasnmitted packet
    esp_now_register_send_cb(OnDataSent);

    // Register peer
    // peerInfo.channel = 0;
    peerInfo.encrypt = false;

    memcpy(peerInfo.peer_addr, broadcastAddress_1, 6);
    if (esp_now_add_peer(&peerInfo) != ESP_OK) {
        Serial.println("Failed to add peer");
        return;
    }
}

void loop() {
    mySwitch.loop(); // MUST call the loop() function first

    // Set values to send
    strcpy(myData.a, "Start");
    myData.b = random(1, 20);
    myData.c = 1.2;
    myData.d = true;

    if (mySwitch.getState() == 1) {
        if (!message_sent) {
            // Serial.println("The switch: ON -> OFF");
            // digitalWrite(LED_BUILTIN, LOW);
            esp_err_t result = esp_now_send(broadcastAddress_1, (uint8_t*)&myData, sizeof(myData));

            if (result == ESP_OK) {
                Serial.println("Sent with success");
                message_sent = true;
            } else {
                Serial.println("Error sending the data");
            }
            delay(1000);
        }
    } else {
        // digitalWrite(LED_BUILTIN, HIGH);
        // Serial.println("The switch: OFF -> ON");
        message_sent = false;
    }

    // int state = mySwitch.getState();
    // if (state == HIGH)
    //     Serial.println("The switch: OFF");
    // else
    //     Serial.println("The switch: ON");
}
