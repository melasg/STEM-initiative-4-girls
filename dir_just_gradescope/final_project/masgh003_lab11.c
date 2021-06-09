//HD44780 chipset, FSTN positive 16char x2 line display
//  #include <Wire.h>
//  #include <mcp2308.h>
//  #include <mcp23s08.h>
 #include "../../mac proj dir/includes/io.h"
 //#include <../../mac proj dir/avr-headers/avr/io.h>
#include <util/delay.h>
#include "../../mac proj dir/lcd/io.h"

 //liquidcrystal_SPI for MCP23s08 
 //connections 
    //  computer side              LCD side
                       
    // sck (13)  -> [|--U--|] <- +5v
    //              [|     |] <- background led driver out
    // miso (11) -> [|     |] <- D7
    // adrs*     -> [|     |] <- D6
    // adrs*     -> [|     |] <- D5
    // +5V-(4k7)--> [|     |] <- D4
    // CS (10)   -> [|     |] <- E
    //              [|     |] <- RS
    // gnd       -> [|_____|] <- EN2 (if needed)
//atmega1284p connections
    // VSS -> GND
    // VDD -> +5V
    // VE -> 10k potentiometer
    // RS -> PA7
    // R/W -> PA6
    // E -> PA5
    // D0 -> PC0
    // D1 -> PC1
    // ...
    // D& -> PC7

// LCD's R/W to ground 

// void LCD_init();
// void LCD_ClearScreen(void);
// void LCD_WriteCommand (unsigned char Command);
// void LCD_Cursor (unsigned char column);
// void LCD_DisplayString(unsigned char column ,unsigned char *string);
// void delay_ms(int miliSec);


//ok start now
void main() {
    DDRA = 0xFF;
    DDRD = 0xFF;
    _delay_ms(50);

}