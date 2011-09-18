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
    SetCursorRow(row);
    pCurrent += col;
}

void Screen::SetCursorRow(int row)
{
    switch (row)
    {
    case 0:
        pCurrent = buffer;
        break;

    case 1:
        pCurrent = buffer + 2 * LCD_COLS;
        break;

    case 2:
        pCurrent = buffer + LCD_COLS;
        break;

    case 3:
        pCurrent = buffer + 3 * LCD_COLS;
        break;
    }
}

void Screen::Print(char *text)
{
    while (*text)
    {
        *pCurrent++ = *text++;
    }
}

void Screen::Print(char *text, int count)
{
    while (*text && count)
    {
        *pCurrent++ = *text++;
        --count;
    }
    
    while (count)
    {
        *pCurrent++ = ' ';
        --count;
    }
}

void Screen::PrintRow(int row, char *text)
{
    SetCursorRow(row);
    Print(text, LCD_COLS);
}

bool Screen::Display()
{
    return lcdWriteBuffer((uint8_t*)buffer);
}

// Print float with +123.4 format
void Screen::PrintFloat31(float value)
{
    int total;
    int digit;
    if (value >= 0)
    {
        *pCurrent++ = '+';
        value *= 0.01;
    }
    else
    {
        *pCurrent++ = '-';
        value *= -0.01;
    }

    digit = value;  

    *pCurrent++ = digit + '0'; 
    total = digit * 10; 
    value *= 10.0;
    digit = (int)value - total;

    *pCurrent++ = digit + '0';
    total += digit;
    total *= 10; 
    value *= 10.0;
    digit = (int)value - total;

    *pCurrent++ = digit + '0'; 
    total += digit;
    total *= 10; 
    value *= 10.0;
    digit = (int)value - total;

    *pCurrent++ = '.';

    *pCurrent++ = digit + '0';
}

//  Print float with +1234.5 format
void Screen::PrintFloat41(float value)
{
    int total;
    int digit;
    if (value >= 0)
    {
        *pCurrent++ = '+';
        value *= 0.001;
    }
    else
    {
        *pCurrent++ = '-';
        value *= -0.001;
    }

    digit = value;  

    *pCurrent++ = digit + '0'; 
    total = digit * 10; 
    value *= 10.0;
    digit = (int)value - total;

    *pCurrent++ = digit + '0';
    total += digit;
    total *= 10; 
    value *= 10.0;
    digit = (int)value - total;

    *pCurrent++ = digit + '0';
    total += digit;
    total *= 10; 
    value *= 10.0;
    digit = (int)value - total;

    *pCurrent++ = digit + '0'; 
    total += digit;
    total *= 10; 
    value *= 10.0;
    digit = (int)value - total;

    *pCurrent++ = '.';

    *pCurrent++ = digit + '0';
}


