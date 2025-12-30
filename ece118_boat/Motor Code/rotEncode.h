/* Template ver 1.0 W2022
 * File:   rotEncode.h
 * Author: <Tristen Miller>
 * Brief: functions for interacting with the AS5047D rotary encoder
 * Created on <month> <day>, <year>, <hour> <pm/am>
 * Modified on <month> <day>, <year>, <hour> <pm/am>
 */
#ifndef rotEncode_H // Header guard
#define rotEncode_H //
/*******************************************************************************
 * PUBLIC #INCLUDES                                                            *
 ******************************************************************************/
#include "BOARD.h" 

/*******************************************************************************
 * PUBLIC #DEFINES                                                             *
 ******************************************************************************/
/*******************************************************************************
 * PUBLIC TYPEDEFS                                                             *
 ******************************************************************************/
/*******************************************************************************
 * PUBLIC FUNCTION PROTOTYPES                                                  *
 ******************************************************************************/
/**
 * @Function SPI_INIT(void)
 * @param void
 * @return void
 * @brief sets up the Microprocessor for SPI communication using SPI 2. Currently, RD6 is used as the Chip select
 * @note 
 * @author <Tristen Miller,
 * @modified <Tristen Miller>, <2023>.<Feb>.<15> <11:11> <am> */
void SPI_INIT(void);
/**
 * @Function unsigned short getAngle(void)
 * @param void
 * @return a 16-bit value from the ASD5047D encoder
 * @brief sends the command to the ASD5047D to get the value of the angle
 * @note the top two bits are a parity bit (even) and an error bit
 * @author <Tristen Miller,
 * @modified <Tristen Miller>, <2023>.<Feb>.<15> <11:11> <am> */
unsigned short getAngle(void);  
#endif /* LIBRARYTEMPLATE_H */ // End of header guard

