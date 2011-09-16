#include "LcdDriver.h"
#include "Screen.h"

int count;

byte Degree[8] =
{
    B01100,
    B10010,
    B10010,
    B01100,
    B00000,
    B00000,
    B00000,
    B00000
};

byte Thermometer[8] =
{
    B00100,
    B01010,
    B01010,
    B01010,
    B01010,
    B10001,
    B10001,
    B01110
};

byte Screen1[] = 
{
    '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', 
    '2', '2', '2', '2', '2', '2', '2', '2', '2', '2', '2', '2', '2', '2', '2', '2', '2', '2', '2', '2', 
    '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', 
    '3', '3', '3', '3', '3', '3', '3', '3', '3', '3', '3', '3', '3', '3', '3', '3', '3', '3', '3', '3', 
};

byte Screen2[] = 
{
    '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', 
    '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', 
    '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', 
    '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', 
};

//Screen welcomeScreen;

Screen welcomeScreen(
       //12345678901234567890
        "Welcome to Screens.."
        "Second row          "
        "Third row           "
        "Forth row           "
    );
//Screen welcomeScreen2(
//       //12345678901234567890
//        "Welcome to Screens. "
//        "Second row          "
//        "Third row           "
//        "Forth row           "
//    );

//#define DBG_STATE 

#ifndef DBG_STATE
#define DebugState() 
#endif

#define LCD_CMD_COUNT    5
#define LCD_BIT_COUNT    2
#define LCD_SCR_COUNT    (LCD_ROWS * LCD_COLS * LCD_BIT_COUNT + LCD_CMD_COUNT)

void TestTwoBuffersWaiting();
void TestCustomChar();
void TestWriteBuffer();

void setup()
{
    count = 0;
    Serial.begin(28800);
    Serial.print("Startup...\n");
    lcdInit();

    pinMode(13, OUTPUT); 

    delay(1000);
    
    //TestWriteBuffer();
    //TestCustomChar();
    //TestTwoBuffersWaiting();
    
    DebugState();
    while(!lcdLockBuffer())
    {
        delay(1);
    }
    lcdSetCursor(0,0);
    lcdPrint("1 Waited for buffer.");
    lcdSetCursor(0,1);
    lcdPrint("2 Waited for buffer.");
    lcdSetCursor(0,2);
    lcdPrint("3 Waited for buffer.");
    lcdSetCursor(0,3);
    lcdPrint("4 Waited for buffer.");
    lcdWriteBuffer();
    
    delay(333);
    //DebugState();
    
    if(lcdLockBuffer())
    {
        lcdSetCursor(0,0);
        lcdPrint("1 Tested for buffer.");
        lcdSetCursor(0,1);
        lcdPrint("2 Tested for buffer.");
        lcdSetCursor(0,2);
        lcdPrint("3 Tested for buffer.");
        lcdSetCursor(0,3);
        lcdPrint("4 Tested for buffer.");
        lcdWriteBuffer();
    }
    
    DebugState();

    while(!lcdLockBuffer())
    {
        delay(100);
    }
    //DebugState();
    lcdSetCursor(0,0);
    lcdPrint("1111111");
    delay(1000);
    lcdWriteBuffer();

    delay(1000);
}

void loop()
{
    int i;
    unsigned long entry;
    ++count;
    if (count >= 10) count = 0;
    entry = millis();

    if(lcdLockBuffer())
    {
        uint8_t val = 0x30 + count;
        lcdSetCursor(0,0);
        for (i = 0; i < 20; ++i)
        {
            lcdPrint(val);
        }
        lcdSetCursor(0,1);
        for (i = 0; i < 20; ++i)
        {
            lcdPrint(0x30 + count);
        }
        lcdSetCursor(0,2);
        for (i = 0; i < 20; ++i)
        {
            lcdPrint(0x30 + count);
        }
        lcdSetCursor(0,3);
        for (i = 0; i < 20; ++i)
        {
            lcdPrint(0x30 + count);
        }
        lcdWriteBuffer();
    }
    else
    {
        Serial.println("Skipped..");
    }

    entry = millis() - entry;
    
    delay(150 - entry);
}

void TestTwoBuffersWaiting()
{
    if(lcdLockBuffer())
    {
        lcdSetCursor(0,0);
        lcdPrint("1 Tested for buffer.");
        lcdSetCursor(0,1);
        lcdPrint("2 Tested for buffer.");
        lcdSetCursor(0,2);
        lcdPrint("3 Tested for buffer.");
        lcdSetCursor(0,3);
        lcdPrint("4 Tested for buffer.");
        lcdWriteBuffer();
    }

    if(lcdLockBuffer())
    {
        lcdSetCursor(0,0);
        lcdPrint("5 Tested for buffer.");
        lcdSetCursor(0,1);
        lcdPrint("6 Tested for buffer.");
        lcdSetCursor(0,2);
        lcdPrint("7 Tested for buffer.");
        lcdSetCursor(0,3);
        lcdPrint("8 Tested for buffer.");
        lcdWriteBuffer();
    }
    
//    for (int i = 0; i < 2 * LCD_SCR_COUNT; ++i)
//    {
//        //DebugState();
//        handleLcd();
//        delayMicroseconds(50);
//    }
    //DebugState();

    while(true);
}

void TestCustomChar()
{
  lcdCreateChar(1, Degree);
  lcdCreateChar(2, Thermometer);
  
    if(lcdLockBuffer())
    {
        lcdSetCursor(0,0);
        lcdPrint(1);
        lcdPrint(" Degree.");
        
        lcdSetCursor(0,1);
        lcdPrint(2);
        lcdPrint(" Thermometer.");
        lcdWriteBuffer();
    }
    
    while(true);
}

void TestWriteBuffer()
{
    lcdWriteBuffer(Screen1);
    
    while(true);
}

