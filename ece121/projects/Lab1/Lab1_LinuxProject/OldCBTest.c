/***
 * @file CircularBufferTest.c
 * @version 1.0
 * @author Nicholas Kuipers
 * @brief Standalone Test Bench for simulating the circular buffer
 * @note Built around the use of a separate C compiler to run the test bench.
 *      This means the board-specific libraries are not included here
*/

/*******************************************************************************
 * #INCLUDES                                                                   *
 ******************************************************************************/
#include "stdio.h"

/*******************************************************************************
 * PUBLIC #DEFINES                                                             *
 ******************************************************************************/
#define BUFFER_SIZE 16

/*******************************************************************************
 * PUBLIC TYPEDEFS                                                             *
 ******************************************************************************/

/**
 * @brief Circular buffer that can track up to 16 char values. Uses a head
 *      and tail that increment upon each use to read to/write from the buffer
 *      respectively. Further, holds an isFull value to account for when the
 *      buffer is full (head = tail and all values filled)
 * @author Nicholas Kuipers
 */
typedef struct CircBuffer
{
    unsigned char buffer[BUFFER_SIZE];
    int head;
    int tail;
    int isFull;               //bool flag
} CircBuffer;

/*******************************************************************************
 * PUBLIC FUNCTION DECLARATIONS                                                *
 ******************************************************************************/

void initializeCircBuff(CircBuffer* cB);
int PutChar(CircBuffer* cB, char ch);
unsigned char GetChar(CircBuffer* cB);
int getBufferSize(CircBuffer* cB);

/*******************************************************************************
 * TEST BENCH IMPLEMENTATION                                                   *
 ******************************************************************************/

/**
 * @brief Test bench for Circular Buffer -- runs through series of tests checking
 *      for proper results when buffer is empty, full, when wrapping is needed,
 *      and that character values are properly written to and read from the buffer
 */
int main()
{
    CircBuffer cB;
    char testChar = '\0';
    int testResult = 0;
    printf("\nCircular Buffer Test Bench\n================\n");

    //Test 1: Check that the test buffer is properly initialized.
    printf("Test 1: Did the circular buffer correctly initialize?\n");
    initializeCircBuff(&cB);
    if(cB.head == 0 && cB.tail == 0 && cB.isFull == 0)
        printf("Test 1 Success!\n");
    else
    {
        printf("Test 1 FAILED!\n");
        printf("cB.head = %d\n", cB.head);
        printf("cB.tail = %d\n", cB.tail);
        printf("cB.isFull = %d\n", cB.isFull);
    }

    //Test 2: GetChar throws an error when buffer is empty (returns a '\0' null character)
    printf("\nTest 2: Does GetChar return a null character when the buffer is empty?\n");
    testChar = GetChar(&cB);
    printf("Head = %d\n", cB.head);
    printf("Tail = %d\n", cB.tail);
    if(testChar == '\0')
        printf("Test 2 Success!\n");
    else
    {
        printf("Test 2 FAILED\n");
        printf("testChar = %c\n", testChar);
    }
    
    //Test 3: Check that PutChar works correctly
    printf("\nTest 3: PutChar\n");
    testChar = 'a';
    testResult = PutChar(&cB, testChar);
    if(cB.buffer[cB.tail - 1] = 'a')
        printf("Test 3 Success!\n");
    else
    {
        printf("Test 3 FAILED!\n");
        printf("cB.buffer[tail-1] = %c", cB.buffer[cB.tail - 1]);
    }

    //Test 4: Read this written character using GetChar. Check that head & tail = 1
    printf("\nTest 4: GetChar\n");
    testChar = '\0';    //if GetChar works this will change back to 'a'
    testChar = GetChar(&cB);
    printf("Char value at head = 0: %c\n", testChar);
    printf("Head = %d\n", cB.head);
    printf("Tail = %d\n", cB.tail);
    if(testChar == 'a')
        printf("Test 4 Success!\n");
    else
    {
        printf("Test 4 FAILED!\n");
        printf("Character pulled = %c", testChar);
    }

    //Test 5: PutChar, multiple times with consecutive values until buffer is filled
    printf("\nTest 5: PutChar w/Multiple insertions until buffer is full.\n");
    printf("Inserted: ");
    for(testChar = 'a'; testChar < 'g'; testChar++)
    {
        testResult = PutChar(&cB, testChar);
        printf("'%c' ", testChar);
    }
    printf("\n");
    printf("Current value of tail = %d\n", cB.tail);     //should be 7, "halfway there"
    //      Now, fill the rest of the buffer to position 15, at the point where the buffer is about to wrap
    printf("Inserted: ");
    for(testChar = 'g'; testChar < 'o'; testChar++)
    {
        testResult = PutChar(&cB, testChar);
        printf("'%c' ", testChar);
    }
    printf("\n");
    printf("Current values in buffer: \n");
    for(int i = 0; i < BUFFER_SIZE; i++)
    {
        printf("'%c' ", cB.buffer[i]);
    }
    if(cB.tail == 15)
        printf("\nTest 5 Success!\n");
    else
        printf("\nTest 5 FAILED!\n");

    //Test 5.1: Wrapping logic using PutChar
    printf("\nTest5.1: PutChar --> tail wrapping from position 15 to 0 in buffer\n");
    printf("Current value of tail = %d\n", cB.tail);
    printf("Running PutChar...\n");
    PutChar(&cB, testChar);       //testChar currently 'o'
    printf("Current value of tail = %d\n", cB.tail);
    printf("Current values in buffer: \n");
    for(int i = 0; i < BUFFER_SIZE; i++)
    {
        printf("'%c' ", cB.buffer[i]);
    }
    printf("\n");
    if(cB.tail == 0)
        printf("Test 5.1 Success!\n");
    else
        printf("Test 5.1 FAILED!\n");

    //Test 5.2: Does getBufferSize() work properly when tail is behind head?
    printf("\nTest 5.2: Does getBufferSize() work properly when the tail wraps behind the head?\n");
    printf("Buffer size should be 15 after the wrap from 5.1...\n");
    printf("Head = %d\n", cB.head);
    printf("Tail = %d\n", cB.tail);
    testResult = getBufferSize(&cB);
    printf("Buffer size retrieved by function: %d\n", testResult);
    if(testResult == 15)
        printf("Test 5.2 Success!\n");
    else
        printf("Test 5.2 FAILED!\n");



    //Test 5.3: Does isFull properly set on a full buffer?
    printf("\nTest 5.3: Does isFull properly set when buffer becomes full?");
    printf("Running PutChar once again --> buffer will then be completely full\n");
    PutChar(&cB, 'p');
    if(cB.isFull > 0)
        printf("Test 5.3 Success!\n");
    else
    {
        printf("Test 5.3 FAILED!\n");
    }

    //Test 5.4: PutChar on a full buffer
    printf("\nTest 5.4: Does PutChar throw an error on a full buffer?\n");
    printf("Buffer is full. Running PutChar...\n");
    testResult = PutChar(&cB, 'q');
    printf("Function returned a %d, head = %d, tail = %d\n", testResult, cB.head, cB.tail);
    if(testResult == 1 && cB.head == 1 && cB.tail == 1)
        printf("Test 5.4 Success!\n");
    else
        printf("Test 5.4 FAILED!\n");

    //Test 6: GetChar on a full buffer
    printf("\nTest 6: Does GetChar on a full buffer toggle the isFull flag?\n");
    testChar = GetChar(&cB);
    printf("Should have retrieved an 'a'. GetChar retrieved '%c'\n", testChar);
    printf("isFull = %d, Head = %d, Tail = %d\n", cB.isFull, cB.head, cB.tail);
    if(cB.isFull == 0)
        printf("Test 6 Success!\n");
    else   
        printf("Test 6 FAILED!\n");

    //Test 6.1: GetChar wrapping
    printf("\nTest 6.1: Does GetChar properly wrap the head?\n");
    printf("Calling GetChar to position 15 in the buffer...\n");
    printf("Read from buffer: ");
    for(int i = cB.head; i < 15; i++)
    {
        printf("'%c'", GetChar(&cB));
    }
    printf("\nHead = %d, Tail = %d\n", cB.head, cB.tail);
    printf("Calling GetChar one more time to see the wrap...\n");
    printf("GetChar at position 15 = '%c'\n", GetChar(&cB));
    printf("Head = %d, Tail = %d\n", cB.head, cB.tail);
    if(cB.head == 0)
        printf("Test 6.1 Success!\n");
    else
        printf("Test 6.1 FAILED!\n");

    //Test 6.2: GetChar error throwing
    printf("\nTest 6.2: Does GetChar throw a proper error on an empty buffer?");
    printf("Calling GetChar one more time to finish emptying the buffer...\n");
    printf("GetChar at position 0 = '%c'\n", GetChar(&cB));
    printf("Calling GetChar again, should return a null character...\n");
    testChar = GetChar(&cB);
    printf("GetChar with empty buffer = '%c'\n", testChar);
    if(testChar == '\0')
        printf("Test 6.2 Success!\n");
    else
        printf("Test 6.2 FAILED!\n");


    printf("==================\n");
    printf("End of Test Bench\n");


}


/*******************************************************************************
 * PUBLIC FUNCTION IMPLEMENTATIONS                                             *
 ******************************************************************************/

/**
 * @param cB
 * @return void
 * @brief Initializes the values within the circular buffer. The
 *      head and tail of the buffer should be 0, and the buffer is
 *      not full (isFull == 0)
 * @author Nicholas Kuipers
 */
void initializeCircBuff(CircBuffer* cB)
{
    cB->head   = 0;
    cB->tail   = 0;
    cB->isFull = 0;
}

/**
 * @brief Places a character into the circular buffer
 * 
 * @param cB 
 * @param ch 
 * @return int -- 0 if success, 1 if error
 * @author Nicholas Kuipers
 */
int PutChar(CircBuffer* cB, char ch)
{
    if(cB->isFull)
        return 1;          //Return an error: Buffer is already full
    if(getBufferSize(cB) == 15)
        cB->isFull = 1;    //Buffer is full after completion of function
    
    //place char in buffer at tail position, increment tail, then return success
    cB->buffer[cB->tail++] = ch;
    if(cB->tail == 16)             //checks if a wrap back to 0 is necessary
        cB->tail = 0;
    return 0;   //success
}

/**
 * @brief Read a character value from the circular buffer, pointed to by head
 * 
 * @param cB 
 * @return unsigned char value, or null character ('\0') if error
 * @author Nicholas Kuipers
 */
unsigned char GetChar(CircBuffer* cB)
{
    if(getBufferSize(cB) == 0 && !cB->isFull)  //check if the buffer is empty
        return '\0';             //returns a null character
    if(cB->isFull)                             //check if the buffer is full, resets flag if so
        cB->isFull = 0;
    
    char temp = cB->buffer[cB->head];
    if(cB->head < (BUFFER_SIZE - 1))           //check if head is less than 15
        cB->head++;
    else
        cB->head = 0;                          //wrapping condition if head equals 15    
    
    return temp;
}

/**
 * @brief Returns the current size of the circular buffer
 * 
 * @param cB 
 * @return int size of the buffer
 */
int getBufferSize(CircBuffer* cB)
{
    int currentSize = cB->tail - cB->head;

    //Check positive values, otherwise negative values, otherwise 0
    if(currentSize > 0)
    {
        return currentSize;
    }
    else if(currentSize < 0)
    {
        return BUFFER_SIZE + currentSize;
    }
    return 0;
}









