#include <WiFi.h>
#include <esp_now.h>

#include <ToneESP32.h>
#define BUZZER_PIN 21
#define BUZZER_CHANNEL 0

ToneESP32 buzzer(BUZZER_PIN, BUZZER_CHANNEL);

// Structure example to receive data
// Must match the sender structure
typedef struct struct_message
{
    char a[32];
    int b;
    float c;
    bool d;
} struct_message;

// Create a struct_message called myData
struct_message myData;

// callback function that will be executed when data is received
void OnDataRecv(const uint8_t* mac, const uint8_t* incomingData, int len) {
    digitalWrite(LED_BUILTIN, HIGH);
    memcpy(&myData, incomingData, sizeof(myData));
    Serial.print("Bytes received: ");
    Serial.println(len);
    Serial.print("Char: ");
    Serial.println(myData.a);
    Serial.print("Int: ");
    Serial.println(myData.b);
    Serial.print("Float: ");
    Serial.println(myData.c);
    Serial.print("Bool: ");
    Serial.println(myData.d);
    Serial.println();

    buzzer.tone(NOTE_C4, 250);
    buzzer.tone(NOTE_D4, 250);
    buzzer.tone(NOTE_E4, 250);
    buzzer.tone(NOTE_F4, 250);
    buzzer.tone(NOTE_G4, 250);
    buzzer.tone(NOTE_A4, 250);
    buzzer.tone(NOTE_B4, 250);
    buzzer.tone(NOTE_C5, 250);
    delay(250);
    buzzer.tone(NOTE_C5, 250);
    buzzer.tone(NOTE_B4, 250);
    buzzer.tone(NOTE_A4, 250);
    buzzer.tone(NOTE_G4, 250);
    buzzer.tone(NOTE_F4, 250);
    buzzer.tone(NOTE_E4, 250);
    buzzer.tone(NOTE_D4, 250);
    buzzer.tone(NOTE_C4, 250);
    digitalWrite(LED_BUILTIN, LOW);
}

void setup() {
    pinMode(LED_BUILTIN, OUTPUT);   // blue led on chip to notify boot is pressed
    digitalWrite(LED_BUILTIN, LOW); // start off
    // Initialize Serial Monitor
    Serial.begin(115200);

    // Set device as a Wi-Fi Station
    WiFi.mode(WIFI_STA);

    // Init ESP-NOW
    if (esp_now_init() != ESP_OK) {
        Serial.println("Error initializing ESP-NOW");
        return;
    }

    // Once ESPNow is successfully Init, we will register for recv CB to
    // get recv packer info
    esp_now_register_recv_cb(OnDataRecv);
}

void loop() {
}
