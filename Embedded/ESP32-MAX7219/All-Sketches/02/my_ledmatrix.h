//https://majicdesigns.github.io/MD_Parola/class_m_d___parola.html
#include <MD_Parola.h>
#include <MD_MAX72xx.h>
#include <SPI.h>
#include <String>

#define HARDWARE_TYPE MD_MAX72XX::FC16_HW
#define MAX_DEVICES 4
#define CS_PIN 15
#define DIN 23
#define CLK 18

MD_Parola myDisplay = MD_Parola(HARDWARE_TYPE, CS_PIN, MAX_DEVICES);

void startDisplay(){
  // Intialize the object:
  myDisplay.begin();
  // Set the intensity (brightness) of the display (0-15):
  myDisplay.setIntensity(8);
  myDisplay.setInvert(true);
  // Clear the display:
  myDisplay.displayClear();
  //displayText(pText, align, speed, pause, effectIn, effectOut (150 langsam 100 schnller)
  myDisplay.displayText("-EDI-", PA_CENTER, 80, 1500, PA_SCROLL_RIGHT, PA_SCROLL_LEFT);
}
