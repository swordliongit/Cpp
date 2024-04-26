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
 
}
