#include "KeyboardReader.h"

KeyboardReader::KeyboardReader()
{
}

void KeyboardReader::pressKey()
{
    _keyPressed = true;
}

bool KeyboardReader::isKeyPressed()
{
    if (_keyPressed == true) {
        _keyPressed = false;
        return true;
    } else {
        return false;
    }
}