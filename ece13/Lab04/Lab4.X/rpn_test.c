// **** Include libraries here ****
// Standard libraries
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

//CMPE13 Support Library
#include "BOARD.h"



// User libraries
#include "rpn.h"

int main()
{
    BOARD_Init();
    int error;

    printf("\n###### Beginning NKuipers' rpn test harness: ####\n\n");
    
    printf("\nTest 1: Basic addition test:\n");
    char test1[] = "15 32 +";
    double result;
    double expected = 47;
    printf("Testing RPN_Evaluate with \"%s\"... \n ", test1);
    error = RPN_Evaluate(test1, &result);
    if (error) {
        printf("   Failed, RPN_Evaluate produced an error\n");
    } else if (result != expected) {
        printf("   Failed, expected = %f , result = %f\n", expected, result);
    } else {
        printf("   Success!\n");
    }
    
    printf("\nTest 2: Test with Two Operators and newline operator:\n");
    char test2[] = "3 7 + 5 * \n 55";                        //(3 + 7) * 5
    expected = 50;
    printf("Testing RPN_Evaluate with \"%s\"... \n", test2);
    error = RPN_Evaluate(test2, &result);
    if (error) {
        printf("   Failed, RPN_Evaluate produced an error\n");
    } else if (result != expected) {
        printf("   Failed, expected = %f , result = %f\n", expected, result);
    } else {
        printf("   Success!\n");
    }
    
    printf("\nTest 3: Test With Multiple values and All Four Operators\n");
    char test3[] = "10 34 66 + * 2 / 7 4 * + 33 -";                        //10 * (34 + 66) / 2 + (7 * 4) - 33) = 495
    expected = 495;
    printf("Testing RPN_Evaluate with \"%s\"... \n", test3);
    error = RPN_Evaluate(test3, &result);
    if (error) {
        printf("   Failed, RPN_Evaluate produced an error\n");
    } else if (result != expected) {
        printf("   Failed, expected = %f , result = %f\n", expected, result);
    } else {
        printf("   Success!\n");
    }
    
    printf("\nTest 4: Error Check - Not in RPN format (operator cannot operate on two values)\n");
    char test4[] = "8 + 6";           
    expected = 14;
    printf("Testing RPN_Evaluate with \"%s\"... \n", test4);
    error = RPN_Evaluate(test4, &result);
    if (error) {
        printf("Success! -- RPN_Evaluate produced an error\n");
    } else if (result != expected) {
        printf("Failed, RPN_Evaluate generated a false value. Expected = %f, result = %f\n", expected, result);
    } else {
        printf("Failed, RPN_Evaluate did not detect the error\n");
    }
    
    printf("\nTest 5: Test of Stack Overflow\n");
    char test5[] = "5 8 6 3 5 6 2 5 4 3 + * / 4 7 6 3 5 9 8 7 4 7 6 4 8 7 + / / /";
    expected = 0;        //this RPN is invalid so not expecting any value
    printf("Testing RPN_Evaluate with \"%s\"... \n", test5);
    error = RPN_Evaluate(test5, &result);
    if (error) {
        printf("Success! -- RPN_Evaluate produced an error\n");
    } else if (result != expected) {
        printf("Failed, RPN_Evaluate generated a false value. Expected = %f, result = %f\n", expected, result);
    } else {
        printf("Failed, RPN_Evaluate did not detect the error\n");
    }
    
    printf("\nTest 6: Test of Invalid Characters\n");
    char test6[] = "13 6 * 4 & 9 +";
    expected = 0;        //this RPN is invalid so not expecting any value
    printf("Testing RPN_Evaluate with \"%s\"... \n", test6);
    error = RPN_Evaluate(test6, &result);
    if (error) {
        printf("Success! -- RPN_Evaluate produced an error\n");
    } else if (result != expected) {
        printf("Failed, RPN_Evaluate generated a false value. Expected = %f, result = %f\n", expected, result);
    } else {
        printf("Failed, RPN_Evaluate did not detect the error\n");
    }
    
    printf("\nTest 7: Too Many Operators\n");
    char test7[] = "13 5 + * / 7 55";
    expected = 0;        //this RPN is invalid so not expecting any value
    printf("Testing RPN_Evaluate with \"%s\"... \n", test7);
    error = RPN_Evaluate(test7, &result);
    if (error) {
        printf("Success! -- RPN_Evaluate produced an error\n");
    } else if (result != expected) {
        printf("Failed, RPN_Evaluate generated a false value. Expected = %f, result = %f\n", expected, result);
    } else {
        printf("Failed, RPN_Evaluate did not detect the error\n");
    }
    
    

    printf("Testing ProcessBackspaces:\n");
    char test_pb1[] = "123\b34";
    ProcessBackspaces(test_pb1);
    printf("result    : %s\n", test_pb1);
    printf("should be : 1234\n");
    BOARD_End();
    while (1);
}


