/*
 * File:   NegotiationTest.c
 * Authors: Luca Altaffer taltaffe@ucsc.edu
 *          Nicholas Kuipers
 *
 * Created on March 10, 2022, 9:46 AM
 */


#include "xc.h"
#include "Negotiation.h"
#include "BOARD.h"
#include <stdio.h>

int main(void)
{

    BOARD_Init();

    //Introduction
    printf("Welcome to Negotiation Test!\n\n");

    /*
     *  Function 1: NegotiationHash()
     *  This function takes in a NegotiationData unsigned 16-bit integer, and returns another NegotiationData value
     */
    //Test 1.1: Testing the negotiation with a simple value that should return a specific value
    printf("Test 1: Basic Test for NegotiationHash()\n");
    printf("Testing Negotiation Hash with value 3. Expected return = 9\n");

    if(NegotiationHash(3) == 9)
        printf("Test passed! Negotiation hash returned expected value.\n\n");
    else
        printf("Test failed. Negotiation hash did not return the expected output.\n\n");

    //Test 1.2: Another basic test. The parameter 0 should return a 0.
    printf("Test 1.2: Testing Negotiation Hash with value 0.\nExpected return = 0\n");

    if(NegotiationHash(0) == 0)
        printf("Test passed! Negotiation hash returned expected value.\n\n");
    else
        printf("Test failed. Negotiation hash did not return the expected output.\n\n");
    
    //Test 1.3: Testing the hash function with the value 12345. Expecting a return of 43182
    printf("Test 1.3: Testing Negotiation Hash with value 12345.\nExpected return = 43182\n");

    if(NegotiationHash(12345) == 27825)
        printf("Test passed! Negotiation hash return expected value.\n\n");
    else
        printf("Test failed. Negotiation hash did not return the expected output.\n\n");
    

    /*
     *  Function 2: NegotiationVerify()
     *  This function takes in two uint16_t values and returns a single int value (TRUE or FALSE)
     *      This determines whether or not our hash calculation matches that of the challenger's hash
     */
    //Test 2.1: Testing with a hash of 3 and a result (commitment) of 9 from the challenger. Should return a TRUE 
    printf("Test 2.1: Basic Test of NegotiationVerify()\n");
    printf("Testing Negotiation Verify with secret 3 and commitment 9. Expected return = TRUE\n");

    if(NegotiationVerify(0x0003,0x0009) == TRUE)
        printf("Test passed! Negotiation verify returned true.\n\n");
    else
        printf("Test failed. Negotiation verify did not return the expected output.\n\n");
    
    //Test 2.2: Test with a hash of 3 and a result (commitment) of 10. Should be a FALSE
    printf("Test 2.2: Second Basic Test of NegotiationVerify()\n");
    printf("Testing Negotiation Verify with secret 3 and commitment 10. Expected return = FALSE\n");

    if(NegotiationVerify(0x0003,0x000A) == FALSE)
        printf("Test passed! Negotiation verify returned true.\n\n");
    else
        printf("Test failed. Negotiation verify did not return the expected output.\n\n");
    
    //Test 2.3: Test with a hash of 12345 and a commitment of 43182. Should return a TRUE.
    printf("Test 2.2: Third Basic Test of NegotiationVerify()\n");
    printf("Testing Negotiation Verify with secret 12345 and commitment 43182. Expected return = TRUE\n");
    
    if(NegotiationVerify(12345,27825) == TRUE)
        printf("Test passed! Negotiation verify returned true.\n\n");
    else
        printf("Test failed. Negotiation verify did not return the expected output.\n\n");

    /*
     *  Function 3: NegotiateCoinFlip()
     *  This function takes in two uint16_t values (from player and opponent)
     *  and returns an outcome of either HEADS or TAILS
     */
    //Test 3.1: Basic test of NegotiateCoinFlip()
    printf("Test 3.1: Basic Test for NegotiateCoinFlip()\n");
    printf("Testing negotiate coin flip with 0x00FF and 0x00FE. Expected return = HEADS\n");

    if(NegotiateCoinFlip(0x00FF, 0x00FE) == HEADS)
        printf("Test passed! Negotiate coin flip returned HEADS.\n\n");
    else
        printf("Test failed. Negotiate coin flip did not return the expected output.\n\n");

    //Test 3.2: A second basic test, this time with the parameters matching. Expecting a value of TAILS
    printf("Test 3.2: A second Basic Test for NegotiateCoinFlip()\n");
    printf("Testing negotiate coin flip with 0x00FF and 0x00FF. Expected return = TAILS\n");

    if(NegotiateCoinFlip(0x00FF, 0x00FF) == TAILS)
        printf("Test passed! Negotiate coin flip returned TAILS.\n\n");
    else
        printf("Test failed. Negotiate coin flip did not return the expected output.\n\n");
    


    while(1);
}

