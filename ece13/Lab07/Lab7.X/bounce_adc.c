// **** Include libraries here ****
// Standard libraries
#include <stdio.h>
#include <string.h>

//CMPE13 Support Library
#include "BOARD.h"

// Microchip libraries
#include <xc.h>
#include <sys/attribs.h>

// User libraries
#include "Ascii.h"
#include "Oled.h"
#include "OledDriver.h"

// **** Set macros and preprocessor directives ****

#define VOLTAGE_WINDOW 5
// **** Declare any datatypes here ****

typedef struct {
    uint8_t event;
    int16_t voltage;
} ADCresult;

// **** Define global, module-level, or external variables here ****

ADCresult adc;
int potValue = 0;

// **** Declare function prototypes ****

int main(void)
{
    BOARD_Init();

// Enable interrupts for the ADC
    IPC6bits.AD1IP = 2;
    IPC6bits.AD1IS = 0;
    IEC1bits.AD1IE = 1;

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

    /***************************************************************************************************
     * Your code goes in between this comment and the following one with asterisks.
     **************************************************************************************************/
    printf("Welcome to NKuipers' lab6 part3 (bounce_adc).  Compiled on %s %s.\n",__TIME__,__DATE__);
    OledInit();
    char *outputValue = malloc(25);        //assign memory for outputValue so its values can be changed by sprintf
    //Initially draw the screen, since while loop only rewrites the screen when the adc changes
    sprintf(outputValue, "Potentiometer Reading\n%4i\n%3i%c", adc.voltage, (adc.voltage * 100) / 1023, '%');
    OledDrawString(outputValue);
    OledUpdate();    
    while (1)
    {
        if(adc.event == 1)
        {
            adc.event = 0;
            sprintf(outputValue, "Potentiometer Reading\n%4i\n%3i%c", adc.voltage, (adc.voltage * 100) / 1023, '%');
            OledDrawString(outputValue);
            OledUpdate();
        }
    }
  
    BOARD_End();
    while(1);
    
    /***************************************************************************************************
     * Your code goes in between this comment and the preceding one with asterisks
     **************************************************************************************************/
}

/**
 * This is the interrupt for the ADC1 peripheral. It will trigger whenever a new ADC reading is available
 * in the ADC buffer SFRs, ADC1BUF0 - ADC1BUF7.
 * 
 * It should not be called, and should communicate with main code only by using module-level variables.
 */
void __ISR(_ADC_VECTOR, ipl2auto) AdcHandler(void)
{
    // Clear the interrupt flag.
    IFS1bits.AD1IF = 0;
    
    int previousValue = adc.voltage;
    /*
     *  bufferSum is the sum of all buffers associated with the potentiometer.
     *      Then, if statement that checks:
     *          - bufferSum greater than initial voltage window
     *          - bufferSum is between 0 and 1023
     *          - bufferSum and previousValue have a difference greater than 3
     */
    int bufferSum = (ADC1BUF0 + ADC1BUF1 + ADC1BUF2 + ADC1BUF3 + ADC1BUF4 + ADC1BUF5 + ADC1BUF6 + ADC1BUF7) / 8;
    if(bufferSum > VOLTAGE_WINDOW && bufferSum >= 0 && bufferSum <= 1023 && 
      ((bufferSum - previousValue > 3) || (previousValue - bufferSum > 3)))
    {
        adc.voltage = bufferSum;
        adc.event = 1;
    }


}