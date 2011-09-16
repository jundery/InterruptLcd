#ifndef SCREEN_H
#define SCREEN_H

#include "LcdDriver.h"

class Screen
{
public:
    Screen();
    Screen(char* baseScreen);
    
    void SetCursor(int col, int row);
    
    void Print(char* row);
    void Print(char* row, int count);
    
    bool Display();
    
private:
    uint8_t buffer[LCD_ROWS * LCD_COLS];
    uint8_t* pCurrent;
};

#endif
