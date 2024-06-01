#ifndef TodoList_h
#define TodoList_h

#include <M5paper.h>
#include <Globals.h>
#include <VaultDiver.h>

class TodoList {
public:
    void init();
private:
    TaskHandle_t TodoListHandle;
    M5paper m5paper;
    void readDataVault(int& touchPosX, int& touchPosY, char textMatrix[7][33]);
    void TodoListTask();
    void initButtonData();
    static void TodoListTaskf(void* pvParameters);
    void processTouch(int touchPosX, int touchPosY);
    void drawTodoList(char textMatrix[DISPLAY_MAX_ROWS][DISPLAY_MAX_COLS]);
    void drawLogo();
    int getBoxStartPosY(int rowId);
    int getBoxStopPosY(int rowId);
    VaultDiver diver;
};

#endif
