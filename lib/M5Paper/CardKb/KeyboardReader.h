#ifndef KeyboardReader_h
#define KeyboardReader_h

class KeyboardReader {
public:
    KeyboardReader();
    void pressKey();
    bool isKeyPressed();

private:
    bool _keyPressed = false;
};

#endif
