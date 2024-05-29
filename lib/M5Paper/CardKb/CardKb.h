#ifndef CardKb_h
#define CardKb_h

#include "KeyboardReader.h"
#include <Arduino.h>
#include <Wire.h>

#define CARDKB_ADDR 0x5F
#define BACKSPACE 8

class CardKb {
public:
    void scan();
    char getChar();
    bool isKeyPressed();

private:
    char _lastChar;
    KeyboardReader _keyboard;
};

#endif
