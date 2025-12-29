/** main.c
 *  @project ECE 121 - Lab 0 (Part 2)
 *  @auth Nicholas Kuipers
 *  @due 1/21/2023
 * 
 *  @purpose Build an 8-bit counter that increments every 250ms by default, with separate function for 5ms.
 *      Counter displays current value on the 8 LEDs sequentially -- counter is reset upon button press, or when it reaches above 255
 */

//Instructor-provided libraries
#include "BOARD.h"
//C or board-specific libraries
#include <stdint.h>                //enables use of uint8_t
#include <xc.h>
//Student-created libraries
#include "LEDs.h"
#include "Buttons.h"

//Global variables
#define NOPS_FOR_5MS    6235              //verified through oscilloscope to generate ~5ms intervals (accuracy of 4.99884ms)
uint8_t LEDbits = 0;

//in-file functions
void checkLEDCounterReset();
void NOPdelay_5ms();
void NOPdelay_250ms();

/* main() function for main_part2.c
 * Initializes the board, leds, and buttons. While loop runs forever, and on each iteration:
 *      - sets the LEDs to the current counter value, then increments the counter
 *      - checks the LED counter for one of two reset parameters
 *      - runs a delay loop (blocking code) that runs for either 5ms or 250ms, depending on user selection (default = 250ms)     
 */
int main()
{
    BOARD_Init();
    LEDs_Init();
    Buttons_Init();
    while (1)
    {   
        setLEDValues(LEDbits++);
        checkLEDCounterReset();
        //NOPdelay_5ms();
        NOPdelay_250ms();
    }
    BOARD_End();
    while(1);
}


/* Checks if the counter reaches its max value (255) or if any button was pressed.
 *      If either parameter is true, resets the counter and updates the LEDs to reflect 0
 */
void checkLEDCounterReset()
{
    if((LEDbits > 255) || checkAnyButtonPress())
        {
            LEDbits = 0;
            setLEDValues(LEDbits);
        }
}

/* Blocking code that delays operations for 5ms
 */
void NOPdelay_5ms()
{
    for(int i = 0;i < NOPS_FOR_5MS; i++)
    {  asm("nop");  }
}

/* Blocking code that delays operations for 250ms by running the 5ms delay function 50 times.
 *      Includes a separate check to the reset parameters that occurs on every loop cycle (5ms)
 *
 */
void NOPdelay_250ms()
{
    for(int i = 0;i < 50; i++)
    {  
        NOPdelay_5ms();  
        checkLEDCounterReset();
    }
}



