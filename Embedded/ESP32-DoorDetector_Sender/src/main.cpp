/*
 * This ESP32 code is created by esp32io.com
 *
 * This ESP32 code is released in the public domain
 *
 * For more detail (instruction and wiring diagram), visit https://esp32io.com/tutorials/esp32-switch
 */

#include <WiFi.h>
#include <esp_now.h>


#include <ezButton.h>
ezButton mySwitch(17); // create ezButton object that attach to ESP32 pin GPIO17

uint8_t broadcastAddress_1[6] = {0x8C, 0xCE, 0x4E, 0x8C, 0x64, 0x44};

// Structure example to send data
// Must match the receiver structure
typedef struct struct_message
{
    char a[32];
    int b;
    float c;
    bool d;
} struct_message;

// Create a struct_message called myData
struct_message myData;

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
    Serial.begin(115200);


    pinMode(LED_BUILTIN, OUTPUT);   // blue led on chip to notify boot is pressed
    digitalWrite(LED_BUILTIN, LOW); // start off
    // Set device as a Wi-Fi Station
    WiFi.mode(WIFI_STA);
    // switch setup
    mySwitch.setDebounceTime(0); // set debounce time to 50 milliseconds

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

    if (mySwitch.isPressed()) {
        Serial.println("The switch: OFF -> ON");
        digitalWrite(LED_BUILTIN, HIGH);
        esp_err_t result = esp_now_send(broadcastAddress_1, (uint8_t*)&myData, sizeof(myData));

        if (result == ESP_OK) {
            Serial.println("Sent with success");
        } else {
            Serial.println("Error sending the data");
        }
        delay(1000);
    }

    if (mySwitch.isReleased()) {
        digitalWrite(LED_BUILTIN, LOW);
        Serial.println("The switch: ON -> OFF");
    }

    // int state = mySwitch.getState();
    // if (state == HIGH)
    //     Serial.println("The switch: OFF");
    // else
    //     Serial.println("The switch: ON");
}
