#include "Screen.h"
#include <string.h>

Screen::Screen()
{
    memset(buffer, ' ', LCD_ROWS * LCD_COLS);
    pCurrent = buffer;
}

Screen::Screen(char* baseScreen)
{
    for (int row = 0; row < LCD_ROWS; ++row)
    {
        SetCursor(0, row);
        Print(baseScreen + row * LCD_COLS, LCD_COLS);
    }
    pCurrent = buffer;
}

void Screen::SetCursor(int col, int row)
{
    switch (row)
    {
        case 0:
            pCurrent = buffer + col;
            break;
            
        case 1:
            pCurrent = buffer + 2 * LCD_COLS + col;
            break;
            
        case 2:
            pCurrent = buffer + LCD_COLS + col;
            break;
            
        case 3:
            pCurrent = buffer + 3 * LCD_COLS + col;
            break;
    }
}

void Screen::Print(char *row)
{
    while (*row)
    {
        *pCurrent++ = *row++;
    }
}

void Screen::Print(char *row, int count)
{
    
    while (*row && count)
    {
        *pCurrent++ = *row++;
        --count;
    }
}

bool Screen::Display()
{
    return lcdWriteBuffer(buffer);
}

