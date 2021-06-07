//HD44780 chipset, FSTN positive 16char x2 line display
 #include <Wire.h>
 #include <mcp2308.h>
 #include <mcp23s08.h>
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
// LCD's R/W to ground 

