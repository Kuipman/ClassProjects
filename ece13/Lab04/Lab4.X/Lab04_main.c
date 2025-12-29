// **** Include libraries here ****
// Standard libraries
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

//CMPE13 Support Library
#include "BOARD.h"



// User libraries
#include "rpn.h"
#include "stack.h"

// **** Set macros and preprocessor directives ****
// The lab calls for 60 characters of user input
#define MAX_INPUT_LENGTH 60

int main() {
    BOARD_Init();

    char rpn_sentence[MAX_INPUT_LENGTH + 2];
    double result;
    int error_code = 0;

    printf("Welcome to NKuipers'S RPN calculator.  Compiled on %s %s", __DATE__, __TIME__);
    while (1) 
    {
        printf("\n==================================\n\nEnter floats and + - / * in RPN format: ");
        fgets(rpn_sentence, sizeof (rpn_sentence), stdin);
        error_code = RPN_Evaluate(rpn_sentence, &result);
        switch (error_code)
        {
        case RPN_ERROR_INVALID_TOKEN:
            printf("ERROR: INVALID TOKEN. Please try again.\n");
            break;
        case RPN_ERROR_STACK_OVERFLOW:
            printf("ERROR: STACK OVERFLOW. Please try again.\n");
            break;
        case RPN_ERROR_STACK_UNDERFLOW:
            printf("ERROR: STACK UNDERFLOW. Please try again.\n");
            break;
        case RPN_ERROR_DIVIDE_BY_ZERO:
            printf("ERROR: DIVISION BY ZERO. Please try again.\n");
            break;
        case RPN_ERROR_TOO_FEW_ITEMS_REMAIN:
            printf("ERROR: TOO FEW REMAINING ITEMS. Please try again.\n");
            break;
        case RPN_ERROR_TOO_MANY_ITEMS_REMAIN:
            printf("ERROR: TOO MANY REMAINING ITEMS. Please try again.\n");
            break;
        case RPN_NO_ERROR:
            printf("RPN Result = %f\n", result);
            break;
        default:
            printf("General Error. Please try again.\n"); 
            break;
        }
    }

    while (1);
}
