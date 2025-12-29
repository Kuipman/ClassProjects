/***
 *  @file FreeRunningTimer.c
 *  @version 0.1
 *  @author Nicholas Kuipers
 * 
 *  @brief Utilizes Timer5 (a "Type B timer") in the Pic32 to create a free running timer that runs at the rate of
 *    microseconds. Allows for the return of 32-bit unsigned int values depicting the current millisecond and microsecond values
 *    tracked in the system.
*/

/*******************************************************************************
 * #INCLUDES                                                                   *
 ******************************************************************************/

#include "FreeRunningTimer.h"

/*******************************************************************************
 * PRIVATE #DEFINES                                                            *
 ******************************************************************************/

/*******************************************************************************
 * PRIVATE VARIABLES                                                            *
 ******************************************************************************/

unsigned int currentMillis, currentMicros, loopMillis;
uint8_t LED_tracker;


/*******************************************************************************
 * PRIVATE FUNCTIONS PROTOTYPES                                                 *
 ******************************************************************************/

/*******************************************************************************
 * PUBLIC FUNCTION IMPLEMENTATIONS                                             *
 ******************************************************************************/

/**
 * @brief Initializes Timer5 to be a free running timer that generates an interrupt on every
 *    millisecond (i.e. when the respective value in the Period Register is reached)
 * @param  none
 * @return none
 * @author Nicholas Kuipers
 */ 
void FreeRunningTimer_Init(void)
{
    // First, clear prior values in Timer5 and set desired values for a 16-bit synchronous timer
    T5CONCLR = 0xFFFF;     // Timer5 control register is reset
    TMR5CLR  = 0xFFFF;     // Timer counter initially set to 0
    PR5CLR   = 0xFFFF;     // Period counter initially set to 0
    T5CONSET = 0x0020;     // Prescaler = 1:4
    PR5SET   = 0x2710;     // Period register = 10,000
    
    // Counters tracking the milliseconds and microseconds are initially 0
    currentMillis = 0;
    currentMicros = 0;
    loopMillis    = 0;     // used locally in main() to count elapsed time since previous timer update
    
    // set the Timer5 interrupt, begins the free running timer immediately
    IPC5bits.T5IP = 1;          // Timer5 Interrupt Priority of 1
    IPC5bits.T5IS = 1;          // Sub-priority of 1
    IEC0bits.T5IE = 1;          // Activates Timer 5 interrupt
    T5CONSET = 0x8000;          // Timer5 ON
}

/**
 * @brief Returns a 32-bit value depicting the current millisecond counter value tracked
 *    by the system
 * @param None
 * @return current value in milliseconds tracked by the system
   */
unsigned int FreeRunningTimer_GetMilliSeconds(void)
{
    return currentMillis;
}

/**
 * @brief Returns a 32-bit value depicting the current microsecond counter value tracked
 *    by the system
 * @param None
 * @return current value in microseconds tracked by the system
   */
unsigned int FreeRunningTimer_GetMicroSeconds(void)
{
    return currentMicros + TMR5/10;
}

/*******************************************************************************
 * PRIVATE FUNCTIONS IMPLEMENTATIONS                                           *
 ******************************************************************************/

/*******************************************************************************
 * INTERRUPTS AND HANDLERS                                                     *
 ******************************************************************************/


/**
 * @brief Interrupt Service Routine called when the TMR5 register is 
 *  equal to the value in the PR5 register, which occurs every 1 millisecond
 */
void __ISR(_TIMER_5_VECTOR, ipl3auto) Timer5IntHandler(void)
{
    IFS0bits.T5IF = 0;        // clear the interrupt flag
    currentMillis += 1;
    currentMicros += 1000;
    
#if DEBUG_FRT
    loopMillis    += 1;
#endif /* DEBUG_FRT */
}

/*******************************************************************************
 * FREE_RUNNING_TIMER TEST BENCH                                               *
 ******************************************************************************/

/**
 * @brief Test bench for FRT does the following:
 *      - Initializes Timer5 (in addition to regular initializations)
 *      - Checks if 2 seconds have passed (based on currentMillis value). Print output,
 *          toggle LED and status of an I/O pin, then reset currentMillis value to 0
 * @return int 
 */
#if DEBUG_FRT

int main()
{
    // Initializations
    BOARD_Init();
    Protocol_Init(115200);       
    FreeRunningTimer_Init();
    
    // Send initial debug message showing compile date and time
    char* outputMessage = (char*)malloc(128);
    sprintf(outputMessage, "Lab 2 Part 1: FRT Test. Compiled on: %s at %s", __DATE__, __TIME__);
    Protocol_SendDebugMessage(outputMessage);

    while(1)
    {
        if(loopMillis >= 2000)
        {
            memset(outputMessage, 0, 128);
            sprintf(outputMessage, "Current Count: %i Milliseconds and %i Microseconds\n", FreeRunningTimer_GetMilliSeconds(), FreeRunningTimer_GetMicroSeconds());
            Protocol_SendDebugMessage(outputMessage);
            loopMillis = 0;
            LED_tracker ^= 0x01;
            setLEDValues(LED_tracker);    // toggles LED0 and digital pin 26
        }
    }
    free(outputMessage);    // this will never be reached -- adding for brevity
    BOARD_End();
}

#endif /* FRT_TESTBENCH */






