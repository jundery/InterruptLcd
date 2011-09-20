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
        printRow(row, baseScreen + row * LCD_COLS);
    }
    pCurrent = buffer;
}

void Screen::setCursor(int col, int row)
{
    setCursorRow(row);
    pCurrent += col;
}

void Screen::setCursorRow(int row)
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

void Screen::print(char ch)
{
    *pCurrent++ = ch;
}

void Screen::print(char *text)
{
    while (*text)
    {
        *pCurrent++ = *text++;
    }
}

void Screen::print(char *text, int count)
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

void Screen::printRow(int row, char *text)
{
    setCursorRow(row);
    print(text, LCD_COLS);
}

bool Screen::display()
{
    return lcdWriteBuffer((uint8_t*)buffer);
}

// Print float with +123.4 format
void Screen::printFloat31(float value)
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
void Screen::printFloat41(float value)
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

void Screen::print(int value)
{
    int digit;
    bool printing = false;
    
    if (value < 0)
    {
        print('-');
        value *= -1;
    }
    
    if (value > 10000 || printing)
    {
        digit = value / 10000;
        print(digit + '0');
        value -= digit * 10000;
        printing = true;
    }
    if (value > 1000 || printing)
    {
        digit = value / 1000;
        print(digit + '0');
        value -= digit * 1000;
        printing = true;
    }
    if (value > 100 || printing)
    {
        digit = value / 100;
        print(digit + '0');
        value -= digit * 100;
        printing = true;
    }
    if (value > 10 || printing)
    {
        digit = value / 10;
        print(digit + '0');
        value -= digit * 10;
        printing = true;
    }

    print(value + '0');
}


