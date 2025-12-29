#include <stdio.h>
#include <stdint.h>

/**
 * @brief Converts a Little Endian integer to a Big Endian, or vice versa
 * @param num, the 32-bit/4-byte value to be converted
 * @return the Endian conversion as another unsigned int 
 * @author Nicholas Kuipers
 */
unsigned int convertEndian(unsigned int *num)
{
    unsigned int input  = *num;
    unsigned int result = 0;       // we add values from num to this int
    uint8_t      temp   = 0;
    for(unsigned int i = 0; i < 4; i++)
    {
        temp = input >> (8*i);
        temp &= 0xFF;   // singles out least significant byte
        result |= temp << (24 - (8*i));  // writes to opposite byte in the resulting integer
    }
    return result;
}

int main()
{
    printf("\nEndian Conversion Logic Test Bench\n\n");
    printf("First test: conversion of integer 23501 (0x5BCD) to 52571 (0xCD5B)");
    unsigned int testnum1 = 23501;
    printf("\nTest integer %i to hex: %#08X\n", testnum1, testnum1);
    //Here goes nothing
    unsigned int result1 = convertEndian(&testnum1);
    printf("\nResult: %i , and hex: %#08X\n", result1, result1);
    if(result1 = 0x5BCD)
        printf("Test 1 Success!\n");
    else
        printf("Test 1 Failed.\n");

    printf("\nTest 2: Conversion of integer 2136751873 (0x7F5C3F01) to 20929663 (0x13F5C7F)");
    unsigned int testnum2 = 2136751873;
    unsigned int result2 = convertEndian(&testnum2);
    printf("\nResult: %i , and hex: %#08X\n", result2, result2);
    if(result2 = 0x13F5C7F)
        printf("Test 2 Success!\n");
    else
        printf("Test 2 Failed.\n");
    
    printf("\nTest 3: Does this change back?");
    unsigned int testnum3 = result2;
    unsigned int result3 = convertEndian(&testnum3);
    printf("\nResult: %i , and hex: %#08X\n", result3, result3);
    if(result3 = testnum1)
        printf("Test 3 Success!\n");
    else
        printf("Test 3 Failed.\n");
}