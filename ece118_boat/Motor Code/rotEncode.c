/* Template ver 1.0 W2022
 * File:   rotEncode.c
 * Author: <Tristen Miller>
 * Brief: 
 * Created on <Feb> <15>, <2023>, <11:15> <am>
 * Modified on <Feb> <15>, <2023>, <11:15> <am>
 */
/*******************************************************************************
 * #INCLUDES                                                                   *
 ******************************************************************************/
#include "rotEncode.h" // The header file for this source file.
#include "FRT.h"
#include "BOARD.h"
#include "Protocol.h"
#include "MessageIDs.h"
#include <stdio.h>
#include <xc.h>
#include <stdlib.h>
/*******************************************************************************
 * PRIVATE #DEFINES                                                            *
 ******************************************************************************/
/*******************************************************************************
 * PRIVATE TYPEDEFS                                                            *
 ******************************************************************************/
/*******************************************************************************
 * PRIVATE FUNCTIONS PROTOTYPES                                                 *
 ******************************************************************************/

/*******************************************************************************
 * PUBLIC FUNCTION IMPLEMENTATIONS                                             *
 ******************************************************************************/
void SPI_INIT(void)
{
    SPI2CON = 0;
    //SPI2CON2=0;
    SPI2STAT = 0;
    SPI2BUF = 0;
    //SPI2BRG = 0;
    TRISDbits.TRISD6 = 0; //Chip select pin, set as output
    TRISGbits.TRISG7 = 1; //MISO pin, set as input
    TRISGbits.TRISG8 = 0; //MOSI pin, set as output
    //TRISGbits.TRISG6 = 1; //SCLK pin, set as input-- to be toggled later
    TRISGbits.TRISG6 = 0;
    PORTDbits.RD6 = 1; //This is our chip select. 
    SPI2CONbits.CKE = 0;
    SPI2BRG = 15;
    SPI2CONbits.MODE16 = 1;
    SPI2CONbits.MSTEN = 1;

    SPI2CONbits.ON = 1;
}

unsigned short getAngle(void)
{

    PORTDbits.RD6 = 0;
    int foo = TMR5;
    while (!(TMR5 - foo > 6));
    SPI2BUF = 0xFFFF; //Command to read angle from encoder
    while (!SPI2STATbits.SPIRBF);


    foo = TMR5;
    while (!(TMR5 - foo > 5));
    PORTDbits.RD6 = 1;
    unsigned short garbage = SPI2BUF;

    PORTDbits.RD6 = 0;
    SPI2BUF = 0xC000; //No op command to encoder
    while (!SPI2STATbits.SPIRBF);
    foo = TMR5;
    while (!(TMR5 - foo > 6));
    PORTDbits.RD6 = 1;
    unsigned short angle = SPI2BUF;
    return angle;



}
/*******************************************************************************
 * PRIVATE FUNCTION IMPLEMENTATIONS                                            *
 ******************************************************************************/
#ifdef ENCODER_TEST

void main(void)
{
    BOARD_Init();
    LEDS_INIT();
    Protocol_Init(STANDARD_BAUDRATE);
    timerInit();
    SPI_INIT();
#ifndef SPECIAL_TEST
    char message[128];
    sprintf(message, "Tristen Miller's rotEncode.c -- Compiled on %s %s\n", __DATE__, __TIME__);
    Protocol_SendDebugMessage(message);
    unsigned short angle = getAngle();
    angle &= 0x3FFF; //Get rid of the top two bits
    unsigned int long_angle = angle;
    unsigned int reverse = convertEndian(&long_angle);
    reverse = reverse >> 16;
    Protocol_SendPacket(3, ID_ROTARY_ANGLE, &reverse);
    while (1) {
        if (FRT_getMilliSec() % 10 == 0) {

            unsigned short angle2 = getAngle();

            angle2 &= 0x3FFF;


            if (abs(angle - angle2) > 10) {
                angle = angle2;
                long_angle = angle;
                reverse = convertEndian(&long_angle);
                reverse = reverse >> 16;
                Protocol_SendPacket(3, ID_ROTARY_ANGLE, &reverse);
            }
        }
    }
#endif

#ifdef SPECIAL_TEST
    //Just a quick sanity check. For some reason the rotary encoder isn't going below 0x2000, so I'm lead to believe that bit 13 is always being set on, somehow.
    //This works correctly, however, So I don't think it's a problem with my SendPacket
    unsigned char foo = 0x00;
    unsigned char bar = 0x00;
    unsigned char please[] = {foo, bar};
    Protocol_SendPacket(3, ID_ROTARY_ANGLE, please);
    while (1);
#endif
}

#endif
