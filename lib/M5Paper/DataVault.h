#ifndef DATAVAULT_H
#define DATAVAULT_H

#include <Globals.h>

#define LOOT_TOUCH_POS_X "touchPosX"
#define LOOT_TOUCH_POS_Y "touchPosY"
#define LOOT_KEY_COUNT "keyCount"
#define LOOT_TEXT_MATRIX "textMatrix"
#define LOOT_CHECK_BOXES "checkBoxes"

struct DataVault {
    int touchPosX;
    int touchPosY;
    int keyCount;
    char textMatrix[DISPLAY_MAX_ROWS][DISPLAY_MAX_COLS];
    char checkBoxes[DISPLAY_MAX_ROWS][BOX_PARAMS];
};

#endif
