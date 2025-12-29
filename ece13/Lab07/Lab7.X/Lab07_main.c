// **** Include libraries here ****
// Standard libraries
#include <stdio.h>
#include <string.h>

//CSE13E Support Library
#include "BOARD.h"
#include "Ascii.h"
#include "Leds.h"
#include "Adc.h"
#include "Buttons.h"
#include "Oled.h"
#include "OledDriver.h"

// Microchip libraries
#include <xc.h>
#include <sys/attribs.h>

// User Libraries


// **** Set any macros or preprocessor directives here ****
// Set a macro for resetting the timer, makes the code a little clearer.
#define TIMER_2HZ_RESET() (TMR1 = 0)
#define LONG_PRESS 5                     //uses freeRunningTime ticks rather than seconds
#define VOLTAGE_WINDOW 5                 //utilized with ADC


// **** Set any local typedefs here ****
typedef enum {
    SETUP, SELECTOR_CHANGE_PENDING, COOKING, RESET_PENDING
} OvenState;

typedef enum {
    BAKE, TOAST, BROIL
} OvenMode;

typedef enum {
    TIME, TEMP, NONE
} Selection;

typedef struct {
    OvenState state;       //provided by instructor
    OvenMode mode;
    char *oven_Top;
    char *oven_Bottom;
    int timeSetting_minutes;
    int timeSetting_seconds;
    int tempSetting;
    Selection select;
} OvenData;

// **** Declare any datatypes here ****

// **** Define any module-level, global, or external variables here ****
char *output_OLED;                //stores the output sent to the OLED display
char *modeDisplay;                //used in updateOvenOLED
char LED_Pattern = 0x00;          //Tracks current pattern of LEDs
uint32_t freeRunningTimer = 0;    //this timer consistently increments with every TIMER_TICK
uint32_t FRT_StoredValue = 0;     //this is used to store the current freerunning time when an event occurs
uint32_t LED_Checker = 0;         //used with LED logic

uint8_t TIMER_TICK = FALSE;       //event flag, set to true for every call to the 5hz interrupt
uint8_t BUTTON_INPUT = FALSE;     //event flag, set to true when a button is pressed
uint8_t ADC_INPUT = FALSE;        //event flag, set to true when ADC is adjusted

uint8_t currentButtonValue = 0;    //stores current value of inputs received from board
uint16_t currentADCValue = 0;      //current value of potentiometer on board

uint8_t LED_Transition = 0;       //this is set when state is initially set to COOKING -- reflects the starting value of timer

// **** Put any helper functions here ****
void OvenDataReset(OvenData *ovenData);          //This function initializes our struct
void updateOvenOLED(OvenData *ovenData);         //This function updates the output_OLED string when called
void runOvenSM(OvenData *ovenData);              //Called with an event flag, updates state machine if necessary
void changeSelector(OvenData *ovenData);         //toggles Selection value in OvenData struct (if applicable)
void changeMode(OvenData *ovenData);             //changes OvenMode value in OvenData struct
void changeSelectedValue(OvenData *ovenData);    //changes selected value using the ADC
int decrementTimer(OvenData *ovenData);          //reduces timer by 1 in cooking mode
void updateLEDS();           //determines the rate at which the LEDs turn off during cooking

int main()
{
    BOARD_Init();
    
     //initalize timers and timer ISRs:
    // <editor-fold defaultstate="collapsed" desc="TIMER SETUP">
    
    // Configure Timer 2 using PBCLK as input. We configure it using a 1:16 prescalar, so each timer
    // tick is actually at F_PB / 16 Hz, so setting PR2 to F_PB / 16 / 100 yields a .01s timer.

    T2CON = 0; // everything should be off
    T2CONbits.TCKPS = 0b100; // 1:16 prescaler
    PR2 = BOARD_GetPBClock() / 16 / 100; // interrupt at .5s intervals
    T2CONbits.ON = 1; // turn the timer on

    // Set up the timer interrupt with a priority of 4.
    IFS0bits.T2IF = 0; //clear the interrupt flag before configuring
    IPC2bits.T2IP = 4; // priority of  4
    IPC2bits.T2IS = 0; // subpriority of 0 arbitrarily 
    IEC0bits.T2IE = 1; // turn the interrupt on

    // Configure Timer 3 using PBCLK as input. We configure it using a 1:256 prescaler, so each timer
    // tick is actually at F_PB / 256 Hz, so setting PR3 to F_PB / 256 / 5 yields a .2s timer.

    T3CON = 0; // everything should be off
    T3CONbits.TCKPS = 0b111; // 1:256 prescaler
    PR3 = BOARD_GetPBClock() / 256 / 5; // interrupt at .5s intervals
    T3CONbits.ON = 1; // turn the timer on

    // Set up the timer interrupt with a priority of 4.
    IFS0bits.T3IF = 0; //clear the interrupt flag before configuring
    IPC3bits.T3IP = 4; // priority of  4
    IPC3bits.T3IS = 0; // subpriority of 0 arbitrarily 
    IEC0bits.T3IE = 1; // turn the interrupt on;

    // </editor-fold>
    //initialize ADC
    ///*
    // Set B2 to an input so AN2 can be used by the ADC.
    TRISBbits.TRISB2 = 1;

    // Configure and start the ADC
    AD1CHSbits.CH0SA = 2; // add B2 to the mux
    AD1PCFGbits.PCFG2 = 0; // add b2 to the ADC
    AD1CSSLbits.CSSL2 = 1; // and add b2 to the scanner

    AD1CON1 = 0; // start with 0
    AD1CON1bits.SSRC = 0b111; // auto conversion
    AD1CON1bits.ASAM = 1; // auto sample

    AD1CON2 = 0; // start with 0
    AD1CON2bits.SMPI = 7; // one interrupt per 8 samples

    AD1CON3 = 0; // start with 0
    AD1CON3bits.SAMC = 29; // long sample time
    AD1CON3bits.ADCS = 50; // long conversion time
    
    AD1CON1bits.ADON = 1; // and finally turn it on
     //*/
    
    //Introduction to Lab 7 and beginning of student code
    printf("Welcome to NKuipers' Lab07 (Toaster Oven).  Compiled on %s %s.", __TIME__, __DATE__);
    
    /* First batch of code = initializations */
    OledInit();                       //Initialize the OLED display
    ButtonsInit();                    //Initialize our buttons
    LEDS_INIT();                      //Initialize our LEDs
    OvenData ovenData;                //Initialize our struct that tracks our oven data
    OvenDataReset(&ovenData);         //Assigns initial values to our ovenData struct
    output_OLED = malloc(100);        //Assigns memory to our output string that updates the OLED
    modeDisplay = malloc(10);         //Assigns memory to be used with every instance of updateOvenOLED
    currentADCValue = (ADC1BUF0 + ADC1BUF1 + ADC1BUF2 + ADC1BUF3 + ADC1BUF4 + ADC1BUF5 + ADC1BUF6 + ADC1BUF7) / 8;

    /*
     *  While loop runs the following:
     *      - checks TIMER_TICK event, if TRUE:
     *          - sets TIMER_TICK event to false
     *          - if in cooking state: 
     *              - decrements second counter
     *              - LED_Pattern decrements (bit-shift left 1) for every 1/8th of cooking time passed
     *          - updates output_OLED
     *      - checks INPUT_RECEIVED event, if TRUE:
     *          - sets INPUT_RECEIVED to false
     *          - updates output_OLED
     */
    while (1){
        // Add main loop code here:
        // check for events
        // on event, run runOvenSM()    (only needs to run when 100hz interrupt returns event flag)
        // clear event flags
        if(TIMER_TICK == TRUE)
        {
            if(ovenData.state == COOKING)
            {
                runOvenSM(&ovenData);
            }
            TIMER_TICK = FALSE;
        }
        if(ADC_INPUT == TRUE && ovenData.state == SETUP)
            changeSelectedValue(&ovenData);
        if(BUTTON_INPUT == TRUE)
        {
            BUTTON_INPUT = FALSE;
            runOvenSM(&ovenData); 
        }
        updateOvenOLED(&ovenData);
        OledDrawString(output_OLED);
        LEDS_SET(LED_Pattern);
        OledUpdate();
    };
    
    BOARD_End();
    while(1);
}

/*The 5hz timer is used to update the free-running timer and to generate TIMER_TICK events*/
void __ISR(_TIMER_3_VECTOR, ipl4auto) TimerInterrupt5Hz(void)
{
    IFS0CLR = 1 << 12;                //clears the interrupt flag

    freeRunningTimer++;               //increment the freeRunningTimer
    if(freeRunningTimer % 5 == 0)     //every 5 times the interrupt is called (~1 second) the event flag is set
        TIMER_TICK = TRUE;
}

/*The 100hz timer is used to check for button and ADC events*/
void __ISR(_TIMER_2_VECTOR, ipl4auto) TimerInterrupt100Hz(void)
{
    // Clear the interrupt flag.
    IFS0CLR = 1 << 8;

    //First we check our button inputs
    currentButtonValue = ButtonsCheckEvents();         //function ButtonsCheckEvents() returns values associated with buttons pressed/released
    if((currentButtonValue != BUTTON_EVENT_NONE) && (currentButtonValue & 0b11110000))
        BUTTON_INPUT = TRUE;                         //event flag set for main function loop
    
    //Next we check the ADC input
    int tempValue = (ADC1BUF0 + ADC1BUF1 + ADC1BUF2 + ADC1BUF3 + ADC1BUF4 + ADC1BUF5 + ADC1BUF6 + ADC1BUF7) / 8;
    if(tempValue > VOLTAGE_WINDOW && tempValue >= 0 && tempValue <= 1023 && 
      ((tempValue - currentADCValue > 3) || (currentADCValue - tempValue > 3)))
    {
        currentADCValue = tempValue;
        ADC_INPUT = TRUE;
    }
    
}
// <editor-fold defaultstate="collapsed" desc="HELPER FUNCTIONS">
void runOvenSM(OvenData *ovenData)
{
    //We will run through each situation where a change occurs, beginning with SETUP
    if(ovenData->state == SETUP)
    {
        if(currentButtonValue & BUTTON_EVENT_3DOWN)         //BTN3 is pressed down
        {
            FRT_StoredValue = freeRunningTimer;
            ovenData->state = SELECTOR_CHANGE_PENDING;
        }
        else if(currentButtonValue & BUTTON_EVENT_4DOWN)    //BTN4 is pressed down
        {
            FRT_StoredValue = freeRunningTimer;
            updateOvenOLED(ovenData);
            LED_Pattern = 0b11111111;
            LED_Transition = ((ovenData->timeSetting_minutes * 60) + ovenData->timeSetting_seconds) / 8;
            ovenData->state = COOKING;
        }
    }
    //Next set of code works with SELECTOR_CHANGE_PENDING state
    else if(ovenData->state == SELECTOR_CHANGE_PENDING)
    {
        if(currentButtonValue & BUTTON_EVENT_3UP)
        {
            if((freeRunningTimer - FRT_StoredValue) < LONG_PRESS)     //elapsed time in button press is less than one second
                changeMode(ovenData);
            else                             //elapsed time is greater than one second
                changeSelector(ovenData);
            
            updateOvenOLED(ovenData);        //in either case something changes, so OLED needs to be updated
            ovenData->state = SETUP;         //in either case the state reverts back to SETUP
        }
    }
    //Next, directions from COOKING state
    else if(ovenData->state == COOKING)
    {
        if(TIMER_TICK == TRUE)
        {
            int temp = decrementTimer(ovenData);
            if(temp == 1)    //if timer has expired (also decrements timer)
            {
                OvenDataReset(ovenData);           //also changes state back to SETUP
                LED_Pattern = 0x00;
                updateOvenOLED(ovenData);
            }
            else
            {
                updateLEDS();
                updateOvenOLED(ovenData);
            }
        }
        if(currentButtonValue & BUTTON_EVENT_4DOWN)
        {
            FRT_StoredValue = freeRunningTimer;
            ovenData->state = RESET_PENDING;
        }
    }
    //lastly, directions from RESET_PENDING
    else if(ovenData->state == RESET_PENDING)
    {
        if(currentButtonValue & BUTTON_EVENT_4UP)
        {
            if((freeRunningTimer - FRT_StoredValue) < LONG_PRESS)
            {
                ovenData->state = COOKING;
                updateOvenOLED(ovenData);
            }
            else
            {
                OvenDataReset(ovenData);
                LED_Pattern = 0x00;
                ovenData->state = SETUP;
                updateOvenOLED(ovenData);
            }
        }
    }
}

//This function sets initial values for our OvenData struct variables (default to BAKE)
void OvenDataReset(OvenData *ovenData)
{
    ovenData->state = SETUP;
    ovenData->mode = BAKE;
    ovenData->oven_Top = malloc(10);
    sprintf(ovenData->oven_Top, "======");      //placeholder for ASCII values
    ovenData->oven_Bottom = malloc(10);
    sprintf(ovenData->oven_Bottom, "======");
    ovenData->timeSetting_minutes = 0;
    ovenData->timeSetting_seconds = 1;
    ovenData->tempSetting = 350;
    ovenData->select = TIME;
}

void updateOvenOLED(OvenData *ovenData)
{
    //char *modeDisplay = malloc(10);
    char selector[2] = {' ',' '};
    
    //switch/case statement changes ovenData mode displayed if necessary
    switch((int)ovenData->mode)
    {
        case BAKE:
            modeDisplay = "BAKE ";
            break;
        case TOAST:
            modeDisplay = "TOAST";
            break;
        case BROIL:
            modeDisplay = "BROIL";
            break;
    }
    switch((int)ovenData->select)
    {
        case TIME:
            selector[0] = '>';
            break;
        case TEMP:
            selector[1] = '>';
            break;
    }
    if(ovenData->state == SETUP || ovenData->state == SELECTOR_CHANGE_PENDING)
    {
        sprintf(ovenData->oven_Top, "======");
        sprintf(ovenData->oven_Bottom, "======");  
    }
    else
    {
        if((ovenData->mode == BAKE) || (ovenData->mode == BROIL))
            sprintf(ovenData->oven_Top, "~~~~~~");
        if((ovenData->mode == BAKE) || (ovenData->mode == TOAST))
            sprintf(ovenData->oven_Bottom, "~~~~~~");
    }
        if(ovenData->mode != TOAST)
            sprintf(output_OLED, "|%c%c%c%c%c%c|  Mode: %s\n|      | %cTime: %1i:%02i\n|------| %cTemp: %3i\n|%c%c%c%c%c%c|", 
                    ovenData->oven_Top[0], ovenData->oven_Top[1], ovenData->oven_Top[2], ovenData->oven_Top[3], ovenData->oven_Top[4], ovenData->oven_Top[5], modeDisplay, 
                    selector[0], ovenData->timeSetting_minutes, ovenData->timeSetting_seconds, 
                    selector[1], ovenData->tempSetting,
                    ovenData->oven_Bottom[0], ovenData->oven_Bottom[1], ovenData->oven_Bottom[2], ovenData->oven_Bottom[3], ovenData->oven_Bottom[4], ovenData->oven_Bottom[5]);
        else
            sprintf(output_OLED, "|%c%c%c%c%c%c|  Mode: %s\n|      | %cTime: %1i:%02i\n|------|           \n|%c%c%c%c%c%c|", 
                    ovenData->oven_Top[0], ovenData->oven_Top[1], ovenData->oven_Top[2], ovenData->oven_Top[3], ovenData->oven_Top[4], ovenData->oven_Top[5], modeDisplay, 
                    selector[0], ovenData->timeSetting_minutes, ovenData->timeSetting_seconds, 
                    ovenData->oven_Bottom[0], ovenData->oven_Bottom[1], ovenData->oven_Bottom[2], ovenData->oven_Bottom[3], ovenData->oven_Bottom[4], ovenData->oven_Bottom[5]);
}

void changeSelector(OvenData *ovenData)
{
    //since BAKE is the only mode with more than one selection, this is the only mode considered
    if(ovenData->mode == BAKE)
    {
        if(ovenData->select == TIME)
            ovenData->select = TEMP;
        else
            ovenData->select = TIME;
    }
}

void changeMode(OvenData *ovenData)
{
    ovenData->select = TIME;
    switch((int)ovenData->mode)
    {
        case BAKE:
            ovenData->mode = TOAST;
            break;
        case TOAST:
            ovenData->mode = BROIL;
            ovenData->tempSetting = 500;
            break;
        case BROIL:
            ovenData->mode = BAKE;
            ovenData->tempSetting = 350;
            break;
    }
}

//STILL NEED TO WORK ON THIS    FOR POTENTIOMETER
void changeSelectedValue(OvenData *ovenData)
{
    if(ovenData->select == TIME)
    {
        int tempCalculation = (currentADCValue * 255) / 1023;       //produces a number between 1 and 100
        int tempMinutes = 0;
        while(tempCalculation >= 60)
        {
            tempCalculation -= 60;
            tempMinutes++;
        }
        ovenData->timeSetting_minutes = tempMinutes;
        ovenData->timeSetting_seconds = tempCalculation;
    }
    else         //temp only available for BAKE, so starts at 300 and goes to 555
        ovenData->tempSetting = 300 + ((currentADCValue * 255) / 1023);
    
    updateOvenOLED(ovenData);
}

//Returns a 1 if timer expires 
int decrementTimer(OvenData *ovenData)
{
    if(ovenData->timeSetting_seconds == 0)      //if seconds counter is at 0
    {
        if(ovenData->timeSetting_minutes == 0)      //if minutes is also at 0, we return the timer has expired
            return 1;
        else                                        //otherwise, decrement minutes and start seconds at 59
        {
            ovenData->timeSetting_minutes--;
            ovenData->timeSetting_seconds = 59;
        }
    }
    else                                       //otherwise, decrement seconds and return that the timer has not yet expired
        ovenData->timeSetting_seconds--;
    return 0;
}

void updateLEDS(void)
{
    LED_Checker++;
    if(LED_Checker == LED_Transition)
    {
        LED_Pattern <<= 1;
        LED_Checker = 0;
    }
}

// </editor-fold>