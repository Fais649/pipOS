#include "Input.h"

Input::Input() { }

void Input::init()
{
    xTaskCreatePinnedToCore(
        Input::scanKbTask,
        "scanKbTask",
        1000,
        NULL,
        4,
        &scanKbHandle,
        0);

    xTaskCreatePinnedToCore(
        Input::scanTpTask,
        "scanTpTask",
        1000,
        NULL,
        3,
        &scanTpHandle,
        0);
}

void Input::scanKbTask(void* pvParameters)
{
    Input* inputInstance = static_cast<Input*>(pvParameters);
    inputInstance->scanKb();
}

void Input::scanTpTask(void* pvParameters)
{
    Input* inputInstance = static_cast<Input*>(pvParameters);
    inputInstance->scanTp();
}

void Input::scanKb()
{
    textArea.refill(vault.textMatrix);

    while (1) {
        cardKb.scan();
        if (cardKb.isKeyPressed()) {
            textArea.handleInput(cardKb.getChar());
            if (xSemaphoreTake(Xenomorph, portMAX_DELAY)) {
                for (size_t i = 0; i < DISPLAY_MAX_ROWS; i++) {
                    vault.keyCount++;
                    strncpy(vault.textMatrix[i], textArea.getCharMatrixRow(i), DISPLAY_MAX_COLS + 1);
                }
                xSemaphoreGive(Xenomorph);
            }
        }

        vTaskDelay(10 / portTICK_PERIOD_MS);
    }
}

void Input::scanTp()
{
    while (1) {
        M5.TP.update();
        if (!M5.TP.isFingerUp()) {
            vTaskDelay(5 / portTICK_PERIOD_MS);
            if (!M5.TP.isFingerUp()) {
                if (xSemaphoreTake(Xenomorph, portMAX_DELAY)) {
                    vault.touchPosX = M5.TP.readFingerX(0);
                    vault.touchPosY = M5.TP.readFingerY(0);

                    xSemaphoreGive(Xenomorph);
                }
            }
        }
        vTaskDelay(10 / portTICK_PERIOD_MS);
    }
}