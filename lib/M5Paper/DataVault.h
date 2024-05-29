#ifndef DataVault_H
#define DataVault_H

#include <Globals.h>
#include <Preferences.h>
#include <freertos/FreeRTOS.h>
#include <freertos/semphr.h>

struct SharedData {
    int touchPosX;
    int touchPosY;
    int keyCount;
    char textMatrix[DISPLAY_MAX_ROWS][DISPLAY_MAX_COLS];
};

SemaphoreHandle_t Xenomorph;
SharedData vault;

class DataVault {
public:
    DataVault();
    Preferences dvpreferences;
    void saveTextMatrix(const char* key, char array[][DISPLAY_MAX_COLS]);
    void getTextMatrix(const char* key, char array[][DISPLAY_MAX_COLS]);
};

#endif
