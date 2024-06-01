#include "VaultDiver.h"

VaultDiver::VaultDiver()
{
    oxygen = xSemaphoreCreateMutex();
    loot.touchPosX = 0;
    loot.touchPosY = 0;
    getTextMatrix(PREFERENCE_TEXT_MATRIX, loot.textMatrix);
}

void VaultDiver::saveTextMatrix(const char* key, char array[][DISPLAY_MAX_COLS])
{
    preferences.begin("textMatrix", false);
    preferences.putBytes(key, (uint8_t*)array,
        DISPLAY_MAX_ROWS * DISPLAY_MAX_COLS * sizeof(char));
    preferences.end();
}

void VaultDiver::getTextMatrix(const char* key, char array[][DISPLAY_MAX_COLS])
{
    preferences.begin("textMatrix", true);
    preferences.getBytes(key, (uint8_t*)array, DISPLAY_MAX_ROWS * DISPLAY_MAX_COLS * sizeof(char));
    preferences.end();
}

void VaultDiver::drop(const char* key, const void* loot, size_t size)
{
    preferences.begin("textMatrix", false);
    preferences.putBytes(key, (uint8_t*)loot, size);
    preferences.end();
}