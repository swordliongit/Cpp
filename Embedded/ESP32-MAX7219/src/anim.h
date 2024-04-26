#ifndef ANIM_H
#define ANIM_H

#include "textfile.h"

#include <MD_Parola.h>
#include <MD_MAX72xx.h>
#include <SPI.h>
#include <iostream>
#include <string.h>

// Uncomment according to your hardware type
#define HARDWARE_TYPE MD_MAX72XX::FC16_HW
//#define HARDWARE_TYPE MD_MAX72XX::GENERIC_HW

// Defining size, and output pins
#define MAX_DEVICES 4 
#define DIN_PIN 23
#define CS_PIN 5
#define CLK_PIN 18

// #define CS_PIN 5


// MD_Parola Display = MD_Parola(HARDWARE_TYPE, DIN_PIN, CLK_PIN, CS_PIN, MAX_DEVICES);
MD_Parola Display = MD_Parola(HARDWARE_TYPE, CS_PIN, MAX_DEVICES);


const uint8_t F_PMAN1 = 6;
const uint8_t W_PMAN1 = 8;
const uint8_t PROGMEM pacman1[F_PMAN1 * W_PMAN1] = {
    0x00, 0x81, 0xc3, 0xe7, 0xff, 0x7e, 0x7e, 0x3c,
    0x00, 0x42, 0xe7, 0xe7, 0xff, 0xff, 0x7e, 0x3c,
    0x24, 0x66, 0xe7, 0xff, 0xff, 0xff, 0x7e, 0x3c,
    0x3c, 0x7e, 0xff, 0xff, 0xff, 0xff, 0x7e, 0x3c,
    0x24, 0x66, 0xe7, 0xff, 0xff, 0xff, 0x7e, 0x3c,
    0x00, 0x42, 0xe7, 0xe7, 0xff, 0xff, 0x7e, 0x3c
};

const uint8_t F_S1 = 2;
const uint8_t W_S1 = 8;
const uint8_t snake1[] =
{
    0x00, 0x00, 0x1e, 0xa1, 0x42, 0x00, 0x00, 0x00,
    0x80, 0x42, 0x35, 0x08, 0x00, 0x00, 0x00, 0x00
};

void startDisplay()
{
    Display.begin();
    Display.setIntensity(8);
    Display.setInvert(false);
    Display.displayClear();
    Display.displayText("Loading...", PA_CENTER, 150, 2000, PA_SCROLL_LEFT, PA_SCROLL_LEFT);
}

void startAnim(String msg)
{
    selectText();
    Display.displayClear();
    Serial.println(msg);
    // Display.setSpriteData(pacman1, W_PMAN1, F_PMAN1, pacman1, W_PMAN1, F_PMAN1);
    Display.displayText(message, PA_CENTER, 150, 2000, PA_SCROLL_LEFT, PA_SCROLL_LEFT);
}

#endif