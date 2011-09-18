#ifndef SCREEN_H
#define SCREEN_H

#include "LcdDriver.h"

class Screen
{
public:
    Screen();
    Screen(char* baseScreen);

    char* GetCursor() const { return pCurrent; }
    void SetCursor(char *pCursor) { pCurrent = pCursor; }
    void SetCursor(int col, int row);
    void SetCursorRow(int row);

    void Print(char *text);
    void Print(char *text, int count);
    void PrintRow(int row, char *text);

    void PrintFloat31(float value);
    void PrintFloat41(float value);

    bool Display();

private:
    char buffer[LCD_ROWS * LCD_COLS];
    char* pCurrent;
};

#endif

