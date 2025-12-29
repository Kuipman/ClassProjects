/*
 *  @file Player.c
 *  @authr Nicholas Kuipers
 *  @date 2/23/2022
 * 
 *  @purpose Definitions for Player.h library
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include "Player.h"
#include "Game.h"       //for macros

 //int array tracks the inventory of the player
typedef struct{
    uint8_t inventory[INVENTORY_SIZE];
    uint8_t inventoryPointer;              //starts at 0 and moves right along inventory array until end is reached
}Player;

static Player currentPlayer;

//static uint8_t player_Inventory[INVENTORY_SIZE];

/**
 * Adds the specified item to the player's inventory if the inventory isn't full.
 * @param item The item number to be stored: valid values are 0-255.
 * @return SUCCESS if the item was added, STANDARD_ERRROR if the item couldn't be added.
 */
int AddToInventory(uint8_t item)
{
    if (currentPlayer.inventoryPointer < 4)
    {
        currentPlayer.inventory[currentPlayer.inventoryPointer] = item;
        currentPlayer.inventoryPointer++;
        return SUCCESS;
    }
    return STANDARD_ERROR;     //if above fails, returns standard error
}

/**
 * Check if the given item exists in the player's inventory.
 * @param item The number of the item to be searched for: valid values are 0-255.
 * @return SUCCESS if it was found or STANDARD_ERROR if it wasn't.
 */
int FindInInventory(uint8_t item)
{
    //Loop checks each element of the inventory array. If an element value matches the item value, return SUCCESS
    for (int i = 0; i < 4; i++)
        if (currentPlayer.inventory[i] == item)
            return SUCCESS;
    //If loop did not find item, return STANDARD_ERROR
    return STANDARD_ERROR;
}