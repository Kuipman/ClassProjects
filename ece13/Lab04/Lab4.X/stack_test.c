// **** Include libraries here ****
// Standard libraries
#include <stdio.h>

//CMPE13 Support Library
#include "BOARD.h"


// User libraries
#include "stack.h"

int main()
{
    BOARD_Init();

    printf("\n###### Beginning nkuipers' stack test harness: ####\n\n");
    
    //Test 1: Initialization Test
    printf("Does StackInit() set the currentItemIndex appropriately?\n");
    struct Stack stack = {};
    StackInit(&stack);
    if (stack.currentItemIndex == -1) {
        printf("Passed");
    } else {
        printf("FAILED");
    }
    
    //Test 2: StackPush() Test
    printf("\nDoes StackPush() push a series of values onto the stack properly?\n");
    StackPush(&stack, 25);
    StackPush(&stack, 37);
    StackPush(&stack, 3);
    if(stack.stackItems[2] == 3 && stack.stackItems[1] == 37 && stack.stackItems[0] == 25)
        printf("Passed");
    else
        printf("FAILED");
    
    //Test 2.5: StackPush() Error Test
    printf("\nDoes StackPush() return an error when it pushes a value onto a full stack?\n");
    for(int i = 3; i < STACK_SIZE; i++)   //this fills the rest of the stack with values
        StackPush(&stack, i);
    if(StackPush(&stack, 15) == STANDARD_ERROR)
        printf("Passed");
    else
        printf("FAILED");
    
    //Test 3.0: StackPop() Test
    printf("\nDoes StackPop() pop a series of values from the stack properly?\n");
    double popTest = 0;
    if(StackPop(&stack, &popTest) == SUCCESS)
        printf("Passed");
    else
        printf("FAILED");
    
    //Test 3.5: StackPop() Error Test
    printf("\nDoes StackPop() return an error when used on an empty stack?\n");
    struct Stack stack2 = {};
    StackInit(&stack2);
    if(StackPop(&stack2, &popTest) == STANDARD_ERROR)
        printf("Passed");
    else
        printf("FAILED");
    
    //Test 4.0: StackIsEmpty() test on an empty stack
    printf("\nDoes StackIsEmpty() return TRUE for an empty stack?\n");
    if(StackIsEmpty(&stack2) == TRUE)
        printf("Passed");
    else
        printf("FAILED");
    
    //Test 4.5: StackIsEmpty() test on a stack with values
    printf("\nDoes StackIsEmpty() return FALSE for a stack that is not empty?\n");
    if(StackIsEmpty(&stack) == FALSE)
        printf("Passed");
    else
        printf("FAILED");
    
    //Test 5.0: StackIsFull() test on a full stack
    printf("\nDoes StackIsFull() return TRUE for a stack that is full?\n");
    if(StackIsFull(&stack) == TRUE)
        printf("Passed");
    else
        printf("FAILED");
    
    //Test 5.5: StackIsFull() test on a stack that is empty (no values)
    printf("\nDoes StackIsFull() return FALSE for a stack that is not full?\n");
    if(StackIsFull(&stack2) == FALSE)
        printf("Passed");
    else
        printf("FAILED");
    
    //Test 6.0: StackGetSize() Test
    printf("\nDoes StackGetSize() return a correct value for a stack without values?\n");
    if(StackGetSize(&stack2) == 0)
        printf("Passed");
    else
        printf("FAILED");
    
    //Test 6.5: StackGetSize() Test 2
    printf("\nDoes StackGetSize() return a correct value for a stack with values?\n");
    StackPush(&stack2, 25);
    StackPush(&stack2, 7);
    if(StackGetSize(&stack2) == 2)
        printf("Passed");
    else
        printf("FAILED");

    BOARD_End();
    //test stackInit:  */
    while (1);
    return 0;
}


