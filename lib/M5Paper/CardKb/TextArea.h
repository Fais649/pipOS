#ifndef TextArea_h
#define TextArea_h

#include "Globals.h"

class TextArea {
public:
    TextArea();
    void refill(char array[][DISPLAY_MAX_COLS]);
    char* getCharMatrixRow(int posY);
    void handleInput(char input);

private:
    int _maxRows;
    int _maxCols;

    char _charMatrix[DISPLAY_MAX_ROWS][DISPLAY_MAX_COLS];
    int _cursorPosY = 0;
    int _cursorPosX = 0;
    int _cursorBlinkChar = '_';
    int _cursorChar = _charMatrix[_cursorPosY][_cursorPosX];

    char _input;
    void cursorRight();
    void cursorLeft();
    void cursorUp();
    void cursorDown();
    void cursorResetX();
    void cursorResetY();
    void cursorRightMax();

    void updateCursorChar();
    void cursorBlinkChar();

    void updateCharAtCurrPos();
    void addNullTerminator(int xOffset);

    bool isNewChar();
    bool isNewBackspace();
    bool isNewEnter();
    bool isNewEsc();
    bool isNewTab();
    bool isNewUp();
    bool isNewDown();
    bool isNewLeft();
    bool isNewRight();

    void handleNewChar();
    void handleBackspace();
    void handleEnter();
    void handleEsc();
    void handleTab();
    void handleUp();
    void handleDown();
};

#endif
