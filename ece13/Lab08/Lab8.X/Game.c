/*
 *  @file Game.c
 *  @authr Nicholas Kuipers
 *  @date 2/23/2022
 * 
 *  @purpose Definitions for Game.h library
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include "Game.h"
#include "Player.h"

 /**
 *   Room struct tracks the title, description, and exit details for the room the player is currently in
 *      - Title and Description are arrays sized from their max length macros
 *      - Each exit value is the room number accessible by the current room, or 0 otherwise
 */
static struct Room {
    char title[GAME_MAX_ROOM_TITLE_LENGTH + 1];
    char description[GAME_MAX_ROOM_DESC_LENGTH + 1];
    uint8_t exit_North;
    uint8_t exit_South;
    uint8_t exit_East;
    uint8_t exit_West;
};

struct Room currentRoom;

//Helper Function, defined further at bottom of .c file
int Pull_File_Data(uint8_t file_num);

/**
 * The following four functions operate when each cardinal direction is called by the user. Each function pulls
 * the room number from the respective direction and calls the helper function Pull_File_Data to gather all
 * room information from that file.
 * @return SUCCESS if the room CAN be navigated to and changing the current room to that new room
 *         succeeded. STANDARD_ERROR otherwise
 */
int GameGoNorth(void)
{
    if(currentRoom.exit_North > 0)
    {
        Pull_File_Data(currentRoom.exit_North);
        return SUCCESS;
    }
    else
        return STANDARD_ERROR;
}

int GameGoEast(void)
{
    if (currentRoom.exit_East > 0)
    {
        Pull_File_Data(currentRoom.exit_East);
        return SUCCESS;
    }
    else
        return STANDARD_ERROR;
}


int GameGoSouth(void)
{
    if (currentRoom.exit_South > 0)
    {
        Pull_File_Data(currentRoom.exit_South);
        return SUCCESS;
    }
    else
        return STANDARD_ERROR;
}


int GameGoWest(void)
{
    if (currentRoom.exit_West > 0)
    {
        Pull_File_Data(currentRoom.exit_West);
        return SUCCESS;
    }
    else
        return STANDARD_ERROR;
}

/**
 * Calls on the helper function Pull_File_Data to gather all information from the room depicted in the
 * STARTING_ROOM macro
 * @return SUCCESS if file info was successfully pulled or STANDARD_ERROR otherwise
 */
int GameInit(void)
{
    int pull = Pull_File_Data(STARTING_ROOM);
    if (pull == SUCCESS)
        return SUCCESS;
    else
        return STANDARD_ERROR;
}

/**
*   This copies the title information from the Room struct into the char array 'title' and ends the array with a
*   NULL-character. The total length of the newly copied array + the NULL-character is returned
*   @return length of array + NULL-character, or 0 if the function fails
*
*/
int GameGetCurrentRoomTitle(char* title)
{
    if (title == NULL)
    {
        title[0] = '\0';
        return 0;
    }
    int returnCounter = 0;
    for (int i = 0; i < GAME_MAX_ROOM_TITLE_LENGTH + 1; i++)
    {
        title[i] = currentRoom.title[i];
        returnCounter++;
        if (currentRoom.title[i] == '\0')
            break;
    }
    return returnCounter;
}

/**
*   This copies the description information from the Room struct into the char array 'desc' and ends the array with a
*   NULL-character. The total length of the newly copied array + the NULL-character is returned
*   @return length of array + NULL-character, or 0 if the function fails
*
*/
int GameGetCurrentRoomDescription(char* desc)
{
    if (desc == NULL)
    {
        desc[0] = '\0';
        return 0;
    }
    int returnCounter = 0;
    for (int i = 0; i < GAME_MAX_ROOM_DESC_LENGTH + 1; i++)
    {
        desc[i] = currentRoom.description[i];
        returnCounter++;
        if (currentRoom.description[i] == '\0')
            break;
    }
    return returnCounter;
}

 /**
 *   This uses the lowest 4 bits of an 8-bit integer to display which exits have relevant room values the current room can access, with
 *   a 1 indicating there is an exit and 0 indicating there is NOT an exit. The order is North, East, South, West.
 *   Ex. 0101 indicates there is an exit to the East and West
 *   @return an 8-bit integer, with the lower four bits being useful
 *
 */
uint8_t GameGetCurrentRoomExits(void)
{
    uint8_t exits = 0b00000000;
    if (currentRoom.exit_North != 0)
        exits ^= 0b00001000;
    if (currentRoom.exit_East != 0)
        exits ^= 0b00000100;
    if (currentRoom.exit_South != 0)
        exits ^= 0b00000010;
    if (currentRoom.exit_West != 0)
        exits ^= 0b00000001;

    return exits;
}



/**
*   Helper function that:
*       - Receives an int that points to the file to be opened
*       - Opens the respective .txt file in binary mode
*       - Pulls and stores information into respective variables in Room struct
*       - Closes the file
*/
int Pull_File_Data(uint8_t file_num)
{
    char filename[25];
    char file_ch = 0x00;
    uint8_t next_length = 0;

    //First we identify the file to be opened, and open the file. We include logic for the event this fails
    sprintf(filename, "RoomFiles/room%i.txt", file_num);
    FILE* fptr = fopen(filename, "r");
    if (fptr == NULL)                                //if the output file does not exist, return standard error
        return STANDARD_ERROR;

    //Now, the first three characters are always "RPG". So, we pass them
    for (int i = 0; i < 3; i++)
        fgetc(fptr);

    //The next character gives the length of the room title
    file_ch = fgetc(fptr);
    //We cast this value as an int, then use this int to determine how many characters to read for the title
    next_length = (uint8_t)file_ch;
    for (int i = 0; i < next_length; i++)
    {
        file_ch = fgetc(fptr);
        currentRoom.title[i] = file_ch;
    }
    currentRoom.title[next_length] = '\0';     //ends the line from preceding function with a null terminator

    /**
    *   From here there could be several versions of the same room depending on the current items in player inventory
    *   For each iteration:
    *       - First character depicts the number of items needed for selected version of room
    *       - Next character(s) depict the ID of the item(s) needed for selected version. Checks for each item, if all items present in inventory versionFlag = TRUE
    *       - Next character depicts the length of the description of the room
    *       - Input each character of the room description into the struct description array. End this with a null terminator
    *       - Next character depicts the number of collectable items from the room
    *       - Next character(s) depict the ID of the item(s). Add item(s) to inventory (if able)
    *       - Next four characters are the exit values
    *       - If versionFlag = TRUE from above, the proper room information was received and the file is closed (even if there is more to read)
    * 
    *   In deciding which version to copy to our struct we use the int value versionFlag, treated as a boolean value. This is
    *   initialized as FALSE but becomes TRUE when the FindInInventory function returns SUCCESS
    */
    
    uint8_t versionFlag = FALSE;

    while (versionFlag == FALSE)
    {
        //Next character gives the number of required items needed for selected version of room
        uint8_t item_req = (uint8_t)fgetc(fptr);
        versionFlag = TRUE;                                    //if a required item is not found, this is reset to false
        //for each required item, get the item ID and check player inventory for that item. If all are present, versionFlag = TRUE, otherwise continue
        for (int i = 0; i < item_req; i++)
        {
            uint8_t item_ID = (uint8_t)fgetc(fptr);
            int isItemPresent = FindInInventory(item_ID);
            if (isItemPresent != SUCCESS)
                versionFlag = FALSE;                 //if a required item not found, this is set to false and does not get reset to true until next iteration of while loop
        }

        //Next character depicts the length of the description of the room
        next_length = (uint8_t)fgetc(fptr);
        //copy each character of the description onto the description array in the Room struct (if versionFlag is true)
        for (int i = 0; i < next_length; i++)
        {
            file_ch = fgetc(fptr);
            if(versionFlag == TRUE)
                currentRoom.description[i] = file_ch;
        }
        currentRoom.description[next_length] = '\0';

        //Next character identifies the collectable items in the room
        uint8_t item_collect = (uint8_t)fgetc(fptr);
        for (int i = 0; i < item_collect; i++)
        {
            uint8_t item_ID = (uint8_t)fgetc(fptr);
            if (versionFlag == TRUE)
            {
                AddToInventory(item_ID);
            }
        }

        //The final four characters represent the exits. Each exit is stored as a uint8_t.
        //Adding logic for the versionFlag will not affect the final version of currentRoom, so we skip adding it
        currentRoom.exit_North = (uint8_t)fgetc(fptr);
        currentRoom.exit_East  = (uint8_t)fgetc(fptr);
        currentRoom.exit_South = (uint8_t)fgetc(fptr);
        currentRoom.exit_West  = (uint8_t)fgetc(fptr);
        
        //if versionFlag == TRUE, then even if there is more to the file we have already found the room version. So, while loop is closed
    }
    fclose(fptr);
    return SUCCESS;
}
