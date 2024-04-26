//https://majicdesigns.github.io/MD_Parola/class_m_d___parola.html
#include <MD_Parola.h>
#include <MD_MAX72xx.h>
#include <SPI.h>
#include <String>

#define HARDWARE_TYPE MD_MAX72XX::FC16_HW
#define MAX_DEVICES 8
#define CS_PIN 15
#define DIN 23
#define CLK 18

MD_Parola myDisplay = MD_Parola(HARDWARE_TYPE, CS_PIN, MAX_DEVICES);

const uint8_t F_PMAN1 = 6;
const uint8_t W_PMAN1 = 8;
const uint8_t PROGMEM pacman1[F_PMAN1 * W_PMAN1] =  // gobbling pacman animation
{
  0x00, 0x81, 0xc3, 0xe7, 0xff, 0x7e, 0x7e, 0x3c,
  0x00, 0x42, 0xe7, 0xe7, 0xff, 0xff, 0x7e, 0x3c,
  0x24, 0x66, 0xe7, 0xff, 0xff, 0xff, 0x7e, 0x3c,
  0x3c, 0x7e, 0xff, 0xff, 0xff, 0xff, 0x7e, 0x3c,
  0x24, 0x66, 0xe7, 0xff, 0xff, 0xff, 0x7e, 0x3c,
  0x00, 0x42, 0xe7, 0xe7, 0xff, 0xff, 0x7e, 0x3c,
};


void startDisplay() {

  // Intialize the object:
  myDisplay.begin();
  // Set the intensity (brightness) of the display (0-15):
  myDisplay.setIntensity(5);
  myDisplay.setInvert(false);
  // Clear the display:
  myDisplay.displayClear();
  //displayText(pText, align, speed, pause, effectIn, effectOut (150 langsam 100 schnller)
  myDisplay.setSpriteData(pacman1, W_PMAN1, F_PMAN1, pacman1, W_PMAN1, F_PMAN1);
  myDisplay.displayText("-EDI-", PA_CENTER, 150, 2000, PA_SPRITE, PA_SPRITE);
  
  //myDisplay.write("text");

}
