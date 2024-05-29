#include "TextArea.h"
#include <Arduino.h>
#include <cstring>

TextArea::TextArea()
{
    _maxRows = DISPLAY_MAX_ROWS;
    _maxCols = DISPLAY_MAX_COLS;
}

void TextArea::refill(char array[][DISPLAY_MAX_COLS])
{
    for (size_t i = 0; i < DISPLAY_MAX_ROWS; i++) {
        int length = strlen(array[i]);
        if (length > 1) {
            _cursorPosX = length - 1;
            _cursorPosY = i;
        }

        strncpy(_charMatrix[i], array[i], DISPLAY_MAX_COLS + 1);
    }
}

char* TextArea::getCharMatrixRow(int posY)
{
    return _charMatrix[posY];
}

void TextArea::handleInput(char input)
{
    _input = input;
    if (isNewChar()) {
        handleNewChar();
    } else if (isNewBackspace()) {
        handleBackspace();
    } else if (isNewEnter()) {
        handleEnter();
    } else if (isNewEsc()) {
        handleEsc();
    } else if (isNewTab()) {
        handleTab();
    } else if (isNewUp()) {
        handleUp();
    } else if (isNewDown()) {
        handleDown();
    }
}

void TextArea::handleNewChar()
{
    if (_cursorPosX < _maxCols) {
        updateCursorChar();
        updateCharAtCurrPos();
        cursorRight();
        cursorBlinkChar();
        addNullTerminator(1);
    }
}

void TextArea::handleBackspace()
{
    if (_cursorPosX > 0) {
        cursorLeft();
        cursorBlinkChar();
        addNullTerminator(1);
    }
}

void TextArea::handleEnter()
{
    if (_cursorPosY < _maxRows) {
        addNullTerminator(0);
        cursorDown();
        cursorResetX();
        cursorBlinkChar();
        addNullTerminator(1);
    }
}

void TextArea::handleTab()
{
    // TODO: Tab Logic
}

void TextArea::handleEsc()
{
    if (_cursorPosX > 0) {
        cursorResetX();
        cursorBlinkChar();
        addNullTerminator(1);
    }
}

void TextArea::handleUp()
{
    if (_cursorPosY > 0) {
        addNullTerminator(0);
        cursorUp();
        cursorRightMax();
        cursorBlinkChar();
        addNullTerminator(1);
    }
}

void TextArea::handleDown()
{
    if (_cursorPosY < _maxRows - 1) {
        addNullTerminator(0);
        cursorDown();
        cursorRightMax();
        cursorBlinkChar();
        addNullTerminator(1);
    }
}

void TextArea::updateCursorChar()
{
    _cursorChar = _input;
}

void TextArea::cursorBlinkChar()
{
    _charMatrix[_cursorPosY][_cursorPosX] = _cursorBlinkChar;
}

void TextArea::updateCharAtCurrPos()
{
    _charMatrix[_cursorPosY][_cursorPosX] = _cursorChar;
}

void TextArea::addNullTerminator(int xOffset)
{
    _charMatrix[_cursorPosY][_cursorPosX + xOffset] = '\0';
}

void TextArea::cursorRight()
{
    if (_cursorPosX < _maxCols) {
        _cursorPosX++;
    }
}

void TextArea::cursorLeft()
{
    if (_cursorPosX > 0) {
        _cursorPosX--;
    }
}

void TextArea::cursorDown()
{
    if (_cursorPosY < _maxRows - 1) {
        _cursorPosY++;
    }
}

void TextArea::cursorUp()
{
    if (_cursorPosY > 0) {
        _cursorPosY--;
    }
}

void TextArea::cursorRightMax()
{
    _cursorPosX = strlen(_charMatrix[_cursorPosY]);
}

void TextArea::cursorResetX()
{
    _cursorPosX = 0;
}

void TextArea::cursorResetY()
{
    _cursorPosY = 0;
}

bool TextArea::isNewChar()
{
    return _input >= 32 && _input <= 126 && _cursorPosX < _maxCols;
}

bool TextArea::isNewBackspace()
{
    return _input == 8 && _cursorPosX > 0;
}

bool TextArea::isNewEnter()
{
    return _input == 13 && _cursorPosY < _maxRows;
}

bool TextArea::isNewEsc()
{
    return _input == 27 && _cursorPosX > 0;
}

bool TextArea::isNewUp()
{
    return _input == 181 && _cursorPosX < _maxCols;
}

bool TextArea::isNewDown()
{
    return _input == 182 && _cursorPosX < _maxCols;
}

bool TextArea::isNewTab()
{
    return _input == 9 && _cursorPosX < _maxCols;
}

bool TextArea::isNewLeft()
{
    return _input == 180 && _cursorPosX < _maxCols;
}

bool TextArea::isNewRight()
{
    return _input == 183 && _cursorPosX < _maxCols;
}