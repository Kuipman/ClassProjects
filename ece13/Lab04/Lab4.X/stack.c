/*
 *  @auth   Nicholas Kuipers
 *  @file   stack.c
 *  
 *  Description:
 *      Lists functions relating to stack and implementing it in Lab 04
 *
 */
#include <stdio.h>
#include <stdlib.h>

#include "stack.h"

/*
 * Function initializes the stack and stack pointer (currentItemIndex)
 */
void StackInit(struct Stack *stack)
{
    stack->currentItemIndex = -1;
    stack->initialized = TRUE;
}

/*
 *  Pushes an element onto the stack. Returns an error if stack is full
 *  NOTE: I wanted to implement StackIsFull here, however I kept getting errors so I'm manually performing the function here
 */
int StackPush(struct Stack *stack, double value)
{
    stack->currentItemIndex++;
    if(stack->currentItemIndex >= STACK_SIZE)
    {
        printf("ERROR: STACK OVERFLOW\n");
        return STANDARD_ERROR;   //stack did not push successfully
    }
    stack->stackItems[stack->currentItemIndex] = value;
    return SUCCESS;    //stack pushed successfully
}

/*
 *  Pops an element from the stack. Returns an error if stack is empty
 */
int StackPop(struct Stack *stack, double *value)
{
    if(stack->currentItemIndex <= -1)
    {
        printf("ERROR: STACK UNDERFLOW\n");
        return STANDARD_ERROR;         //stack did not pop successfully
    }
    *value = stack->stackItems[stack->currentItemIndex];
    stack->currentItemIndex--;
    return SUCCESS;
}

/*
 *  Boolean expression -- returns true (1) if stack is empty, otherwise returns false (0)
 */
int StackIsEmpty(const struct Stack *stack)
{
    if(stack->currentItemIndex == -1)
        return TRUE;
    else
        return FALSE;
}

/*
 *  Boolean expression -- returns TRUE (1) if stack is full or FALSE (0) if stack is empty
 */
int StackIsFull(const struct Stack *stack)
{
    if(stack->currentItemIndex == STACK_SIZE - 1)
        return TRUE;
    else
        return FALSE;
}

/*
 *  Returns the current stack pointer value (minus 1)
 */
int StackGetSize(const struct Stack *stack)
{
    return stack->currentItemIndex + 1;
}