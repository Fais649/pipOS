#include "TodoList.h"
int boxStartPosX = BOX_PADDING;
int boxStopPosX = (BOX_PADDING * 2 + BOX_SIZE);

int checkBoxes[DISPLAY_MAX_ROWS][BOX_PARAMS];

int keyCount = 0;

void TodoList::init()
{
    initButtonData();
    m5paper.init();

    if (diver.inhale()) {
        DataVault loot = diver.dive();

        for (size_t i = 0; i < DISPLAY_MAX_ROWS; i++) {
            memcpy(checkBoxes[i], loot.checkBoxes[i], BOX_PARAMS);
        }

        diver.exhale();
    }

    xTaskCreatePinnedToCore(TodoList::TodoListTaskf, /* Task function */
        "TodoListTaskf", /* Name of the task */
        10000, /* Stack size in words */
        NULL, /* Task input parameter */
        1, /* Priority of the task */
        &TodoListHandle, /* Task handle */
        1); /* Core where the task should run */
}

void TodoList::initButtonData()
{
    // {isDone, startPosX, stopPosX, startPosY, stopPosY}
    for (size_t i = 0; i < DISPLAY_MAX_ROWS; i++) {
        int boxData[5] = { 0, boxStartPosX, boxStopPosX, getBoxStartPosY(i), getBoxStopPosY(i) };
        memcpy(checkBoxes[i], boxData, sizeof(boxData));
    }
}

void TodoList::TodoListTaskf(void* pvParameters)
{
    TodoList* todoListInstance = static_cast<TodoList*>(pvParameters);
    todoListInstance->TodoListTask();
}

void TodoList::TodoListTask()
{
    int touchPosX = 0;
    int touchPosY = 0;
    char textMatrix[DISPLAY_MAX_ROWS][DISPLAY_MAX_COLS];
    while (1) {
        int oldKeyCount = keyCount;
        readDataVault(touchPosX, touchPosY, textMatrix);

        if (touchPosX != 0 && touchPosY != 0) {
            processTouch(touchPosX, touchPosY);
        }

        if (keyCount != oldKeyCount || (touchPosX != 0 && touchPosY != 0)) {
            drawTodoList(textMatrix);
        }

        vTaskDelay(10 / portTICK_PERIOD_MS);
    }
}

int TodoList::getBoxStartPosY(int rowId)
{
    return (rowId * (CANVAS_HEIGHT / (DISPLAY_MAX_ROWS))) + CANVAS_PADDING_TOP;
}

int TodoList::getBoxStopPosY(int rowId)
{
    return (rowId * (CANVAS_HEIGHT / (DISPLAY_MAX_ROWS))) + CANVAS_PADDING_TOP + BOX_SIZE;
}

void TodoList::processTouch(int touchPosX, int touchPosY)
{
    bool touchProcessed = false;
    for (size_t i = 0; i < DISPLAY_MAX_ROWS; i++) {
        if (!touchProcessed && touchPosX >= checkBoxes[i][1] && touchPosX <= checkBoxes[i][2] && touchPosY >= checkBoxes[i][3] && touchPosY <= checkBoxes[i][4]) {
            touchProcessed = true;
            if (checkBoxes[i][0] == 0) {
                checkBoxes[i][0] = 1;
            } else {
                checkBoxes[i][0] = 0;
            }
        }
    }
}

void TodoList::readDataVault(int& touchPosX, int& touchPosY, char textMatrix[DISPLAY_MAX_ROWS][DISPLAY_MAX_COLS])
{
    if (diver.inhale()) {
        DataVault loot = diver.dive();
        touchPosX = loot.touchPosX;
        touchPosY = loot.touchPosY;
        keyCount = loot.keyCount;
        for (size_t i = 0; i < DISPLAY_MAX_ROWS; i++) {
            strncpy(textMatrix[i], loot.textMatrix[i], DISPLAY_MAX_COLS + 1);
        }

        diver.drop(LOOT_CHECK_BOXES, checkBoxes, DISPLAY_MAX_ROWS * BOX_PARAMS * sizeof(int));
        diver.drop(LOOT_TOUCH_POS_X, 0, sizeof(0));
        diver.drop(LOOT_TOUCH_POS_Y, 0, sizeof(0));
        diver.drop(LOOT_KEY_COUNT, 0, sizeof(0));

        diver.exhale();
    }
}

void TodoList::drawTodoList(char textMatrix[DISPLAY_MAX_ROWS][DISPLAY_MAX_COLS])
{
    m5paper.canvas.clear();
    for (size_t i = 0; i < DISPLAY_MAX_ROWS; i++) {
        m5paper.canvas.drawRect(checkBoxes[i][1], checkBoxes[i][3], BOX_SIZE, BOX_SIZE, EPD_BLACK);
        m5paper.canvas.drawRect(checkBoxes[i][1] + 3, checkBoxes[i][3] + 2, BOX_SIZE - 4, BOX_SIZE - 5,
            checkBoxes[i][0] == 0 ? EPD_WHITE : EPD_BLACK);
        m5paper.canvas.drawString(textMatrix[i], checkBoxes[i][1], checkBoxes[i][3]);
    }

    drawLogo();

    m5paper.canvas.pushCanvas(0, 0, UPDATE_MODE_DU4);
}

void TodoList::drawLogo()
{
    m5paper.canvas.fillCircle(850, 450, 10, EPD_BLACK);
    m5paper.canvas.fillCircle(880, 450, 10, EPD_BLACK);
    m5paper.canvas.fillCircle(850, 480, 10, EPD_BLACK);
}

// void TodoList::sleep(){

// }