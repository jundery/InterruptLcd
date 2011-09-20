#ifndef SCREEN_H
#define SCREEN_H

#include "LcdDriver.h"

class Screen
{
public:
    Screen();
    Screen(char* baseScreen);

    char* getCursor() const { return pCurrent; }
    void setCursor(char *pCursor) { pCurrent = pCursor; }
    void setCursor(int col, int row);
    void setCursorRow(int row);

    void print(char ch);
    void print(int value);
    void print(char *text);
    void print(char *text, int count);
    void printRow(int row, char *text);

    void printFloat31(float value);
    void printFloat41(float value);

    bool display();

private:
    char buffer[LCD_ROWS * LCD_COLS];
    char* pCurrent;
};

#endif

