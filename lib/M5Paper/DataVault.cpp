#include "DataVault.h"

DataVault::DataVault()
{
    getTextMatrix(PREFERENCE_TEXT_MATRIX, vault.textMatrix);
}

void DataVault::saveTextMatrix(const char* key, char array[][DISPLAY_MAX_COLS])
{
    dvpreferences.begin("textMatrix", false);
    dvpreferences.putBytes(key, (uint8_t*)array,
        DISPLAY_MAX_ROWS * DISPLAY_MAX_COLS * sizeof(char));
    dvpreferences.end();
}

void DataVault::getTextMatrix(const char* key, char array[][DISPLAY_MAX_COLS])
{
    dvpreferences.begin("textMatrix", true);
    dvpreferences.getBytes(key, (uint8_t*)array, DISPLAY_MAX_ROWS * DISPLAY_MAX_COLS * sizeof(char));
    dvpreferences.end();
}