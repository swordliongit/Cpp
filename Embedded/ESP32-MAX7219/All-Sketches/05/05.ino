/*

         _          _          _ _
        (_)        | |        | (_)
   _ __  ___  _____| | ___  __| |_
  | '_ \| \ \/ / _ \ |/ _ \/ _` | |
  | |_) | |>  <  __/ |  __/ (_| | |
  | .__/|_/_/\_\___|_|\___|\__,_|_|
  | |
  |_|
  www.pixeledi.eu
  LED-Matrix Anzeige via WEB-Server | V1.0 | 12 2021

*/


#include <esp_task_wdt.h>
#include "my_ledmatrix.h"

unsigned long previousMillis = 0;
const long interval = 5 * 1000;
int cnt = 0;

void setup() {
  // Serial port for debugging purposes
  Serial.begin(115200);
  
  startDisplay();
  Serial.println("finished loading");
}

void loop() {
  
  //woof woof
  esp_task_wdt_reset();
   if (myDisplay.displayAnimate()) {
    myDisplay.displayReset();
  }

  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= interval) {
     previousMillis = currentMillis;

     if(cnt==0) changeDisplay("rocket");
     else if(cnt==1) changeDisplay("bunny");
     else if(cnt==2) changeDisplay("ghost");
     else if(cnt==3) changeDisplay("pacman");
     else if(cnt==4) changeDisplay("walker");
     else if(cnt==5) changeDisplay("wave");
     else if(cnt==6) changeDisplay("heart");

     Serial.println(cnt);
     cnt++;

     if(cnt>=7)cnt=0;
  }
 
}
