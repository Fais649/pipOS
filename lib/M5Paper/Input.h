#ifndef Input_h
#define Input_h

#include "VaultDiver.h"
#include <Globals.h>
#include "./CardKb/CardKb.h"
#include "./CardKb/TextArea.h"
#include <M5EPD.h>

class Input {
    public:
        Input();
        void init();
        void scanKb(); 
        static void scanKbTask(void* pvParameters);
        void scanTp(); 
        static void scanTpTask(void* pvParameters);
    private:
        TaskHandle_t scanKbHandle;
        TaskHandle_t scanTpHandle;
        CardKb cardKb;
        TextArea textArea;
        VaultDiver diver;
};

#endif