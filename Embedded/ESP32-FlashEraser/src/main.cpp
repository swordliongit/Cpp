#include <Arduino.h>
#include "esp_system.h"
#include "nvs_flash.h"

void setup()
{
    Serial.begin(115200);
    delay(1000); // Give time for serial connection

    Serial.println("ESP32 Flash Erase Program Starting...");

    // Erase NVS partition
    Serial.println("Erasing NVS flash sector...");
    esp_err_t ret = nvs_flash_erase();
    if (ret != ESP_OK)
    {
        Serial.println("Failed to erase NVS");
        return;
    }

    Serial.println("NVS flash sector erased!");
    Serial.println("Device will restart in 5 seconds...");
    delay(5000);
    ESP.restart();
}

void loop()
{
    // Empty loop - program will restart after erase
}