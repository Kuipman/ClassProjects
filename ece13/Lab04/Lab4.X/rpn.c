/*
 *  @auth   Nicholas Kuipers
 *  @file   rpn.c
 *  
 *  Description:
 *      Lists functions relating to rpn and implementing it in Lab 04
 *
 */
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#include "rpn.h"
#include "stack.h"

#define MAX_TOKEN_SIZE 10

/*
 *   This boolean function is used as part of the evaluation process for RPN_Evaluate()
 */
int checkNumber (const char *token)       //boolean function, returns 1 if true and 0 if false
{
    if(NULL == token || *token == '\0')
        return 0;
    int dotCounter = 0;                  //this is used to facilitate float values (allows for only one dot)
    
    while(*token)
    {
        switch(*token)
        {
            case '.':
                if(++dotCounter > 1)
                    return STANDARD_ERROR;                   //if there is more than one dot, invalid number
                break;
            default:
                if(*token < 48 || *token > 57)
                    return STANDARD_ERROR;
                break;
        }
        token++;
    }
    
    return SUCCESS;        //if end of function is reached, this is a number
}

int RPN_Evaluate(char * rpn_string, double * result)
{
    struct Stack bigStack;
    StackInit(&bigStack);
    const char delim[2] = " ";
    char *token;
    int newLine_Trigger = 0;                //boolean value that will trigger when a newline character is detected within a token
    double operator1 = 0, operator2 = 0;
    
    token = strtok(rpn_string, delim);
    while(token != NULL && *token != '\n')
    {
        if(strlen(token) > MAX_TOKEN_SIZE)                //This RPN file will not accept tokens larger than 10 digits
            return RPN_ERROR_INVALID_TOKEN;
        
        //First checks for operators, which must be by themselves
        if(strlen(token) <= 2)
        {
            char c = *token;
            //if(c == '+' || c == '-' || c == '*' || c == '/' || c == '+\n' || c == '-\n' || c == '*\n' || c == '/\n')
            if(c == '+' || c == '-' || c == '*' || c == '/')
            {
                if(StackGetSize(&bigStack) <= 1)          //stack underflow if it cannot go through two StackPop() operations
                    return RPN_ERROR_STACK_UNDERFLOW;
                StackPop(&bigStack, &operator2);
                StackPop(&bigStack, &operator1);
                switch(*token)
                {
                    case '+':
                        operator1 = operator1 + operator2;
                        StackPush(&bigStack, operator1);
                        token = strtok(NULL, delim);
                        continue;
                    case '-':
                        operator1 = operator1 - operator2;
                        StackPush(&bigStack, operator1);
                        token = strtok(NULL, delim);
                        continue;
                    case '*':
                        operator1 = operator1 * operator2;
                        StackPush(&bigStack, operator1);
                        token = strtok(NULL, delim);
                        continue;
                    case '/':
                        if(operator2 == 0)
                            return RPN_ERROR_DIVIDE_BY_ZERO;
                        operator1 = operator1 / operator2;
                        StackPush(&bigStack, operator1);
                        token = strtok(NULL, delim);
                        continue;
                }
            }
        }
        if(checkNumber(token) == 0)              //the token is an invalid number
            return RPN_ERROR_INVALID_TOKEN;
        if(StackIsFull(&bigStack) == TRUE)       //checks if the stack cannot take another value
            return RPN_ERROR_STACK_OVERFLOW;
        
        StackPush(&bigStack, atof(token));       //number is pushed to the stack
        if (newLine_Trigger == TRUE)
        {
            *token = '\n';
            continue;
        }
        token = strtok(NULL, delim);             //reads next token from string
    }
    
    //We check that the Stack is neither too big nor too small, and output the result
    if(StackGetSize(&bigStack) > 1)
        return RPN_ERROR_TOO_MANY_ITEMS_REMAIN;
    else if(StackGetSize(&bigStack) < 1)
        return RPN_ERROR_TOO_FEW_ITEMS_REMAIN;
    else
        StackPop(&bigStack, result);
    return RPN_NO_ERROR;
}

int ProcessBackspaces(char *rpn_sentence)          //123\b34    //678\b9
{
    int size = strlen(rpn_sentence);
    for (int i = 0; i < size; i++)
    {
        if (rpn_sentence[i] == '\b')
        {
            if (i == 0)
                return STANDARD_ERROR;
            i--;
            for (int j = i; j < size - 2; j++)                 //writes temp_sentence to reflect new sentence after backspace
            {
                rpn_sentence[j] = rpn_sentence[j + 2];
            }
            size = size - 2;
            rpn_sentence[size] = '\0';
        }
    }
    return SUCCESS;
}