// Standard libraries
#include <stdio.h>
#include <math.h>


//User libraries:
#include "BOARD.h"

#ifdef PIC32
// Microchip libraries
#include <xc.h>
#endif


// **** Declare function prototypes ****
double Add(double operand1, double operand2);
double Multiply(double operand1, double operand2);
double AbsoluteValue(double operand);
double FahrenheitToCelsius(double operand);
double Tangent(double operand);
//add more prototypes here
double Divide(double operand1, double operand2);
double Subtract(double operand1, double operand2);
double Average(double operand1, double operand2);
double CelsiusToFahrenheit(double operand1);
double Round(double operand);

int checkInput(char userInput);

void CalculatorRun(void) {
    printf("\n\nWelcome to Nicholas Kuipers' calculator program! Compiled at %s %s\n", __DATE__, __TIME__);

    int calcRunning = 1; //treating as a boolean value since C does not have bool -- loop runs while this == 1
    int inputResult; //result from checkInput -- determines whether one or two operands are needed, 'q' is declared, or invalid entry
    char userInput; //initial char value read from input
    double operand1, operand2, result = 0; //operands are read from input, result is calculated from a function

    do {
        printf("\nEnter a mathematical operation to perform (*,/,+,-,m,a,c,f,t,q,r): ");
        scanf(" %c", &userInput);
        while ((getchar()) != '\n'); //clears the input buffer in case extra keys are pressed
        inputResult = checkInput(userInput); //0 = requires 1 operand, 1 = requires 2 operands, 2 = quit, 3 = invalid input
        if (inputResult == 3) //input not valid
        {
            printf("Error. Selection not valid. Please try again.\n");
        } else if (inputResult == 2) //userInput == 'q'
            calcRunning = 0; //loop terminates, program returns to main()
        else {
            printf("   Enter the first operand: ");
            scanf(" %lf", &operand1);
            if (inputResult == 0) //if function only requires one operand
            {
                printf("\nResult of ");
                switch (userInput) {
                    case 'a':
                        result = AbsoluteValue(operand1);
                        printf("|%lf|: %lf", operand1, result);
                        break;
                    case 'c':
                        result = FahrenheitToCelsius(operand1);
                        printf("%lfF -> C: %lf", operand1, result);
                        break;
                    case 'f':
                        result = CelsiusToFahrenheit(operand1);
                        printf("%lfC -> F: %lf", operand1, result);
                        break;
                    case 't':
                        result = Tangent(operand1);
                        printf("tan(%lf): %lf", operand1, result);
                        break;
                    case 'r':
                        result = Round(operand1);
                        printf("round(%lf): %lf", operand1, result);
                        break;

                    default: printf("Error in calculations. \n");
                }
            } else //function requires both operands
            {
                printf("   Enter the second operand: ");
                scanf(" %lf", &operand2);
                switch (userInput) {
                    case '+':
                        result = Add(operand1, operand2);
                        printf("\nResult of (%lf + %lf): %lf", operand1, operand2, result);
                        break;
                    case '-':
                        result = Subtract(operand1, operand2);
                        printf("\nResult of (%lf - %lf): %lf", operand1, operand2, result);
                        break;
                    case '*':
                        result = Multiply(operand1, operand2);
                        printf("\nResult of (%lf * %lf): %lf", operand1, operand2, result);
                        break;
                    case '/':
                        result = Divide(operand1, operand2);
                        if (result != HUGE)
                            printf("\nResult of (%lf / %lf): %lf", operand1, operand2, result);
                        break;
                    case 'm':
                        result = Average(operand1, operand2);
                        printf("\nResult of avg(%lf , %lf): %lf", operand1, operand2, result);
                        break;
                    default: printf("Error in calculations. \n");
                }
            }
        }
    } while (calcRunning == 1);
    printf("\n\n");
    //BOARD_End();
    //while (1);
}

/********************************************************************************
 * Define the Add function here.
 ********************************************************************************/
double Add(double operand1, double operand2) {
    return operand1 + operand2;
}

/********************************************************************************
 * Define the Subtract function here.
 ********************************************************************************/
double Subtract(double operand1, double operand2) {
    return operand1 - operand2;
}

/********************************************************************************
 * Define the Multiply function here.
 ********************************************************************************/
double Multiply(double operand1, double operand2) {
    return operand1 * operand2;
}

/********************************************************************************
 * Define the Divide function here.
 ********************************************************************************/
double Divide(double operand1, double operand2) {
    if (operand2 == 0) {
        printf("Cannot divide by 0. Terminating current calculation.\n");
        return HUGE;
    } else
        return operand1 / operand2;
}

/********************************************************************************
 * Define the Absolute Value function here.
 ********************************************************************************/
double AbsoluteValue(double operand) {
    if (operand >= 0)
        return operand;
    else
        return operand * -1;
}

/*********************************************************************************
 * Define the Fahrenheit to Celsius function here.
 ********************************************************************************/
double FahrenheitToCelsius(double operand) {
    return (5.0 / 9.0) * (operand - 32.0);
}

/*********************************************************************************
 * Define the Celsius to Fahrenheit function here.
 ********************************************************************************/
double CelsiusToFahrenheit(double operand) {
    return (operand * 1.8) + 32;
}

/********************************************************************************
 * Define the Average function here.
 *******************************************************************************/
double Average(double operand1, double operand2) {
    return (operand1 + operand2) / 2;
}

/*********************************************************************************
 * Define the Tangent function that takes input in degrees.
 ********************************************************************************/
double Tangent(double operand) {
    return tan((operand * M_PI) / 180); //(x*pi)/180) - conversion from degrees to radians
}

/*********************************************************************************
 * Define the Round function here.
 * In order to receive the extra credit your calculator MUST ALSO CORRECTLY utilize
 * this function.
 ********************************************************************************/
double Round(double operand) {
    int modInt = operand; //creates copy of operand w/out decimal
    double calc = operand - (double) modInt;
    if (calc >= 0.5 && calc >= 0) //if the decimal is positive and equal or greater than 0.5, add 1
        modInt++;
    else if (calc <= -0.5 && calc < 0) //if the decimal is negative and equal or less than -.5, subtract 1
        modInt--;
    return (double) modInt;
}

/*
 *   Checks user input, respective output value signifies whether one operand is needed (returns 0), two operands
 *   are needed (returns 1), the user wishes to quit (returns 2), or the user input is invalid (returns 3)
 */
int checkInput(char userInput) {
    if (userInput == 'a' || userInput == 'c' || userInput == 'f' || userInput == 't' || userInput == 'r')
        return 0;
    else if (userInput == '+' || userInput == '-' || userInput == '*' || userInput == '/' || userInput == 'm')
        return 1;
    else if (userInput == 'q')
        return 2;
    else
        return 3;
}

