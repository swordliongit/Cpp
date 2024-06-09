#include <WiFi.h>
#include <esp_now.h>

#include <ArduinoJson.h>
#include <HTTPClient.h>
#include <ToneESP32.h>
#include <esp_wifi.h>
#define BUZZER_PIN 21
#define BUZZER_CHANNEL 0

ToneESP32 buzzer(BUZZER_PIN, BUZZER_CHANNEL);

void log_status();

// Structure example to receive data
// Must match the sender structure
struct struct_message
{
    char a[32];
    int b;
    float c;
    bool d;
};

// Create a struct_message called myData
struct_message myData;

bool trigger_fired = false;


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

    trigger_fired = true;

    digitalWrite(LED_BUILTIN, LOW);
}

void log_status() {
    const char* server_endpoint = "https://dd.swordlion.org/dd/log_status";

    // Serialize JSON document
    JsonDocument doc;
    doc["trigger"] = true;

    std::string json;
    serializeJson(doc, json);


    HTTPClient http;
    // Send request
    http.begin(server_endpoint);
    http.addHeader("Content-Type", "application/json");
    // http.addHeader("Connection", "keep-alive");
    // http.addHeader("Accept-Encoding", "gzip, deflate, br");
    // http.addHeader("Accept", "*/*");
    // http.addHeader("User-Agent", "PostmanRuntime/7.26.8");
    // http.setConnectTimeout(5000);

    int http_response_code = http.POST(json.c_str());
    Serial.println(http.getString());
}

void play_and_log() {

    log_status();

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
}

void setup() {
    pinMode(LED_BUILTIN, OUTPUT);   // blue led on chip to notify boot is pressed
    digitalWrite(LED_BUILTIN, LOW); // start off
    // Initialize Serial Monitor
    Serial.begin(115200);

    // Set the device as a Station and Soft Access Point simultaneously
    WiFi.mode(WIFI_AP_STA);

    // Set device as a Wi-Fi Station
    WiFi.begin("SL-MOBILE", "sword1998");
    while (WiFi.status() != WL_CONNECTED) {
        delay(1000);
        Serial.println("Setting as a Wi-Fi Station..");
    }
    Serial.print("Station IP Address: ");
    Serial.println(WiFi.localIP());
    Serial.print("Wi-Fi Channel: ");
    Serial.println(WiFi.channel());

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
    if (trigger_fired) {
        play_and_log();
        trigger_fired = false;
    }
}
