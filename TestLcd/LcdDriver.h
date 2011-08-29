#ifndef LcdDriver_h
#define LcdDriver_h

#include <stdint.h>

/*
    LCD pin configuration currently only supports 4bit and no R/W pin
    Set the defines below to match your configuration
*/

#define LCD_RS_PIN     12    // Register Select
#define LCD_E_PIN      10    // Enable pin

#define LCD_DB4_PIN    5     // Data pin 4
#define LCD_DB5_PIN    4     // Data pin 5
#define LCD_DB6_PIN    3     // Data pin 6
#define LCD_DB7_PIN    2     // Data pin 7

/*
    Currently only suports 20x4 displays
*/
#define LCD_COLS       20    
#define LCD_ROWS       4


// lcdInit - Needs to be called once to setup the LCD display and interrupt before the 
// display can be used.
void lcdInit();

// Create a custom character in one of the first 8 places
// NOTE: must be called after lcdInit and before anyother methods
void lcdCreateChar(uint8_t location, uint8_t charmap[]);

// lcdLockBuffer - Called to setup a buffer to write to returns true on success and should
// be followed by a matching call to lcdWriteBuffer(). A return value of false means there
// isn't a buffer free to write to.
bool lcdLockBuffer();

// lcdWriteBuffer - Called at the end of an update to prepare the result for display.
void lcdWriteBuffer();

// Set the current write position in the buffer.
void lcdSetCursor(int col, int row);

// Print a nul treminated string of characters caller should limit to the remaining length 
// of the current row. This method advances the current write postition.
void lcdPrint(char* pString);

// Print a byte to the buffer and advance the current write postition.
void lcdPrint(uint8_t value);

#endif
