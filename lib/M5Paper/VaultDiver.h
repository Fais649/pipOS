#ifndef VAULTDIVER_H
#define VAULTDIVER_H

#include <Globals.h>
#include <Preferences.h>
#include <freertos/FreeRTOS.h>
#include <freertos/semphr.h>

#include <DataVault.h>

class VaultDiver {
public:
    Preferences preferences;
    VaultDiver();
    DataVault dive() { return loot; };
    bool inhale()
    {
        return xSemaphoreTake(oxygen, portMAX_DELAY);
    };
    void exhale()
    {
        xSemaphoreGive(oxygen);
    };
    void drop(const char* key, const void* loot, size_t size);
    void saveTextMatrix(const char* key, char array[][DISPLAY_MAX_COLS]);
    void getTextMatrix(const char* key, char array[][DISPLAY_MAX_COLS]);

private:
    SemaphoreHandle_t oxygen;
    DataVault loot;
};

#endif
