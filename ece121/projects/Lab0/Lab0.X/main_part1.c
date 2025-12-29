/** main.c
 *  @project ECE 121 - Lab 0 (Part 1)
 *  @auth Nicholas Kuipers
 *  @due 1/21/2023
 * 
 *  @purpose "Hello World" demonstration of the uC32 and its I/O shield by lighting the 
 *      built-in 8 LEDs via press of any of the 4 built-in buttons
 */ 

//Instructor-provided libraries
#include "BOARD.h"
//C or board-specific libraries
#include <stdint.h>                //enables use of uint8_t
#include <xc.h>
//Student-created libraries
#include "LEDs.h"
#include "Buttons.h"

/* main() function for main_part1.c
 * Initializes the board, leds, and buttons. While loop runs forever, and on each iteration:
 *      - checks for a button press on the I/O shield. If a button is actively pressed down,
 *          all 8 LEDs on the board are driven high. Otherwise, LEDs are driven low.
 */
int main()
{
    BOARD_Init();
    LEDs_Init();
    Buttons_Init();
    while (1)
    {   
        LATE = checkAnyButtonPress();  
    }
    BOARD_End();
    while(1);
}
