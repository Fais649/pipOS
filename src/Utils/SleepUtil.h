#ifndef SLEEP_UTIL_H
#define SLEEP_UTIL_H

#include <Globals.h>
#include <M5paper.h>
#include <VaultDiver.h>

class SleepUtil {
public:
    void init();
private:
    void SleepTask();
    static void SleepTaskf(void* pvParameters);
    TaskHandle_t SleepHandle;
    M5paper m5paper;
    VaultDiver diver;
};

#endif