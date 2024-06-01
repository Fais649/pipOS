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
    textArea.refill(diver.dive().textMatrix);

    while (1) {
        cardKb.scan();
        if (cardKb.isKeyPressed()) {
            textArea.handleInput(cardKb.getChar());
            if (diver.inhale()) {
                DataVault loot = diver.dive();

                for (size_t i = 0; i < DISPLAY_MAX_ROWS; i++) {
                    int countUp = loot.keyCount + 1;
                    diver.drop(LOOT_KEY_COUNT, &countUp, sizeof(countUp));
                    strncpy(loot.textMatrix[i], textArea.getCharMatrixRow(i), DISPLAY_MAX_COLS + 1);
                    diver.drop(LOOT_TEXT_MATRIX, loot.textMatrix, DISPLAY_MAX_ROWS * DISPLAY_MAX_COLS * sizeof(char));
                }

                diver.exhale();
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
                if (diver.inhale()) {
                    uint16_t touchX = M5.TP.readFingerX(0);
                    uint16_t touchY = M5.TP.readFingerY(0);

                    diver.drop(LOOT_TOUCH_POS_X, &touchX, sizeof(touchX));
                    diver.drop(LOOT_TOUCH_POS_Y, &touchY, sizeof(touchY));

                    diver.exhale();
                }
            }
        }
        vTaskDelay(10 / portTICK_PERIOD_MS);
    }
}