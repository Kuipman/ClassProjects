/*
 *  @file Lab08_main.c
 *  @authr Nicholas Kuipers
 *  @date 2/23/2022
 * 
 *  @purpose Driver code for Lab 8
 *
 */

// Standard libraries
#include <string.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

//CSE013E Support Library
#include "UNIXBOARD.h"

// User libraries
#include "Game.h"
#include "Player.h"

// **** Set any macros or preprocessor directives here ****

// **** Declare any data types here ****

// **** Define any global or external variables here ****

// **** Declare any function prototypes here ****
void print_UI(void);
void defineExits(uint8_t, char*);

//Main function
int main()
{
    char userInput;   //stores user input as a single character (extra characters in buffer are removed later in code)

    printf("         Welcome to Dungeon Crawler 1.0 (Patent Pending)\n");

    int initialize = GameInit();            //Opens the first room file and puts respective info into Room struct
    if (initialize == STANDARD_ERROR)       //if GameInit() fails, exits program with a fatal error
        FATAL_ERROR();

    print_UI();                             //prints opening UI with information from first room

    /**   
    *   Loop accomplishes the following:
    *       - Receives user input. First checks if input has only one character and handles inputs that are != 1 character
    *       - If input is only one character, uses a switch statement to check if it matches five selection options and operates based on user input
    *       - Clears the screen to make way for the next UI. This allows for a clean interface with the game
    *       - Prints the next UI
    */
    while (1)
    {
        userInput = getchar();
        if ((getchar()) != '\n')             //if input buffer receives more than one character, clears input buffer and moves to end of loop
        {
            while ((getchar()) != '\n');
            //system("cls");        //use this for VS compiler
            system("clear");        //use this for linux gcc compiler
            print_UI();
            continue;
        }
        else if (userInput == 'n' || userInput == 's' || userInput == 'w' || userInput == 'e' || userInput == 'q')
        {
            switch (userInput)
            {
            case 'n':
                GameGoNorth();
                break;
            case 's':
                GameGoSouth();
                break;
            case 'w':
                GameGoWest();
                break;
            case 'e':
                GameGoEast();
                break;
            case 'q':
                exit(SUCCESS);
            }
        }
        //Following functions are responsible for clearing the screen. Currently selected for linux gcc compiler
        //system("cls");        //use this for VS compiler
        system("clear");        //use this for linux gcc compiler
        print_UI();
    }
}

                                       // **** Helper Functions defined here **** //

/**
*   Initializes char arrays to store the title, description, and exit values of the current room (two are set to ERROR in the event they are not filled properly)
*       - Three functions from Game.h are called to store respective info in each of the three char arrays
*       - The exit logic is assisted by an additional 8-bit integer and additional helper function since the respective function returns another 8-bit integer
*       - The format of the game UI is set and printed from here, with the exits printed using the additional helper function
*/
void print_UI(void)
{
    char title[GAME_MAX_ROOM_TITLE_LENGTH + 1] = "ERROR";
    GameGetCurrentRoomTitle(&title[0]);
    char description[GAME_MAX_ROOM_DESC_LENGTH + 1] = "ERROR";
    GameGetCurrentRoomDescription(&description[0]);
    char exits_char[4] = "   ";
    uint8_t exits_Bin = 0b00000000;
    exits_Bin = GameGetCurrentRoomExits();

    printf("===================================================================================================\n");
    printf("                                       Current Room:  \n");
    printf("                                    **%s**  \n\n\n\n", title);
    printf("                                      Room Description: \n");
    printf("%s                                                \n", description);
    printf("\n\n\n\n");
    printf("Available Exits:  ");
    defineExits(exits_Bin, &exits_char[0]);
    printf("\n\n\n===================================================================================================\n\n\n");
    printf("Where do you wish to go next, traveler? (n, e, w, s, or q for quit): ");
}

/**
*   This takes in the binary values from the GameGetCurrentRoomExits() function from Game.h and a char array to determine whether to print
*       each cardinal direction based on the values from the current room (i.e. prints a direction only if the player can go that direction)
*/

void defineExits(uint8_t exits_Bin, char* exitVals)
{
    if (exits_Bin & 0b00001000)
        printf("North   ");
    if (exits_Bin & 0b00000100)
        printf("East   ");
    if (exits_Bin & 0b00000010)
        printf("South   ");
    if (exits_Bin & 0b00000001)
        printf("West");
}