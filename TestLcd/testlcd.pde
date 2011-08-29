//#include <WProgram.h>
#include "LcdDriver.h"
//#include <LiquidCrystal.h>
	
//LiquidCrystal lcd(2, 3, 7,6,5,4);
//LiquidCrystal lcd(12, 11, 10, 5, 4, 3, 2);
//LiquidCrystal lcd(12, 10, 5, 4, 3, 2);

int count;

void setup()
{
    count = 0;
    Serial.begin(28800);
    Serial.print("Startup...\n");
    lcdInit();
    //lcd.begin(20,4);
    //lcd.setCursor(0,0);
    //lcd.print("hello, world!");
    pinMode(13, OUTPUT); 

    delay(1000);

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
    
    delay(260);
    Serial.println('1');
    
    if(lcdLockBuffer())
    {
         Serial.println('2');
        lcdSetCursor(0,0);
        lcdPrint("1 Tested for buffer.");
        lcdSetCursor(0,1);
        lcdPrint("2 Tested for buffer.");
        lcdSetCursor(0,2);
        lcdPrint("3 Tested for buffer.");
        lcdSetCursor(0,3);
        lcdPrint("4 Tested for buffer.");
         Serial.println('3');
        lcdWriteBuffer();
         Serial.println('4');
    }
    
    while(!lcdLockBuffer())
    {
         Serial.println('5');
        delay(100);
    }
    Serial.println('6');
    lcdSetCursor(0,0);
    lcdPrint("1111111");
    lcdPrint('2');
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
