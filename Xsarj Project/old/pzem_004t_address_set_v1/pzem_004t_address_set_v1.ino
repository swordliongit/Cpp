#include <PZEM004Tv30.h>

PZEM004Tv30 pzem(Serial2,16,17);

void setup() {
  Serial.begin(115200);
}

uint8_t addr = 0x09; //THIS IS THE ADDRESS

void loop() {
    pzem.setAddress(addr);
    Serial.print("Current address:");
    Serial.println(pzem.getAddress());
    Serial.println();
    delay(1000);
}
