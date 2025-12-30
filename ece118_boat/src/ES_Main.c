#include <BOARD.h>
#include <BOAT.h>
#include <xc.h>
#include <stdio.h>
#include "ES_Configure.h"
#include "ES_Framework.h"

#if FINAL_RUN

void main(void)
{
    ES_Return_t ErrorType;

    BOARD_Init();
    BOAT_Init();

    printf("Starting ES Framework: Project BOAT\r\n");
    printf("using the 2nd Generation Events & Services Framework\r\n");


    BOAT_Init();
    //Serial_Init();

    // now initialize the Events and Services Framework and start it running
    ErrorType = ES_Initialize();
    if (ErrorType == Success) {
        ErrorType = ES_Run();

    }
    //if we got to here, there was an error
    switch (ErrorType) {
    case FailedPointer:
        printf("Failed on NULL pointer");
        break;
    case FailedInit:
        printf("Failed Initialization");
        break;
    default:
        printf("Other Failure: %d", ErrorType);
        break;
    }
    for (;;)
        ;

};

#endif

/*------------------------------- Footnotes -------------------------------*/
/*------------------------------ End of file ------------------------------*/
