#include "CardKb.h"

void CardKb::scan()
{
    Wire1.requestFrom(CARDKB_ADDR, 1);
    if (Wire1.available()) {
        char reading = Wire1.read();
        int isKey = (int)reading;
        if (reading != 0) {
            _lastChar = reading;
            _keyboard.pressKey();
        }
    }
}

char CardKb::getChar()
{
    return _lastChar;
}

bool CardKb::isKeyPressed()
{
    return _keyboard.isKeyPressed();
}