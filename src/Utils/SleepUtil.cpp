#include "SleepUtil.h"

void SleepUtil::init()
{
    xTaskCreatePinnedToCore(
        SleepUtil::SleepTaskf, /* Task function */
        "SleepTaskf", /* Name of the task */
        4096, /* Stack size in words */
        NULL, /* Task input parameter */
        4, /* Priority of the task */
        &SleepHandle, /* Task handle */
        0); /* Core where the task should run */
}

void SleepUtil::SleepTaskf(void* pvParameters)
{
    SleepUtil* instance = static_cast<SleepUtil*>(pvParameters);
    instance->SleepTask();
}

void SleepUtil::SleepTask()
{
    while (1) {
        if (digitalRead(M5EPD_KEY_PUSH_PIN) == LOW) {
            vTaskDelay(30 / portTICK_PERIOD_MS); // Debounce delay
            if (digitalRead(M5EPD_KEY_PUSH_PIN) == LOW) {

                m5paper.canvas.fillCircle(880, 480, 2, EPD_BLACK);
                m5paper.canvas.fillCircle(890, 480, 2, EPD_BLACK);
                m5paper.canvas.fillCircle(900, 480, 2, EPD_BLACK);
                m5paper.canvas.fillCircle(910, 480, 2, EPD_BLACK);
                m5paper.canvas.pushCanvas(0, 0, UPDATE_MODE_A2);

                vTaskDelay(300 / portTICK_PERIOD_MS); // Wait for the display to update
                esp_deep_sleep_start();
            }
        }

        vTaskDelay(100 / portTICK_PERIOD_MS);
    }
}
