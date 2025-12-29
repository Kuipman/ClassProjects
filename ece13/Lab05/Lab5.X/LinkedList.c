/**
 * @file
 * This serves as the .c counterpart to the LinkedList.h header file, which provides
 * a doubly-linked list implementation for storing strings
 * 
 * @auth Nicholas Kuipers
 * 
 * @dateCreated 2/2/2022
 */

#include <stdio.h>
#include <stdlib.h>
#include "BOARD.h"

#include "LinkedList.h"

/*
 * This function starts a new linked list by creating a single ListItem that is connected to no other elements.
 * Also checks to ensure memory allocation was successful -- if not, returns NULL
 * @param data The data to be stored in the first ListItem in this new list. Can be any valid 
 *             pointer value.
 * @return A pointer to the malloc()'d ListItem. May be NULL if an error occured.
 * 
 */
ListItem *LinkedListNew(char *data)
{
    ListItem *newList = malloc(sizeof(ListItem));
    //if statement checks if malloc() was successful -- if not, function returns a NULL value
    if(newList == NULL)
    {
        printf("Memory Allocation Failed.\n");
        return NULL;
    }
    newList->previousItem = NULL;
    newList->nextItem = NULL;
    newList->data = data;              //since malloc() was successful, assign parameter data to data value for the new ListItem
    return newList;
}

/*
 * This function allocates a new ListItem containing data and inserts it into the list directly after
 * the ListItem specified by *item in the parameter. This will rearrange the pointers of other elements in the list
 * (if necessary) to ensure it is properly placed after *item.
 * 
 * --if this is passed NULL for *item, this still creates a new ListItem with no previousItem
 * --returns NULL if it cannot malloc() a new ListItem
 * 
 * @param item The ListItem that will be before the newly-created ListItem.
 * @param data The data the new ListItem will point to.
 * @return A pointer to the newly-malloc()'d ListItem.
 * 
 */
ListItem *LinkedListCreateAfter(ListItem *item, char *data)
{
    ListItem *newItem = malloc(sizeof(ListItem));
    //Just as in LinkedListNew() and for all future instances of malloc(), this checks if malloc() was successful
    if(newItem == NULL)
    {
        printf("Memory Allocation Failed.\n");
        return NULL;
    }
    newItem->data = data;              //since malloc() was successful, assign parameter data to data value for the new ListItem
    
    //if *item is a null value, these steps are skipped and this function performs essentially the same as LinkedListNew
    if(item != NULL)
    {
        //first the pointer values for the new ListItem are assigned
        newItem->previousItem = item;
        newItem->nextItem = item->nextItem;
        //then the two (or one) affected element(s) are assigned pointer values that point to the new ListItem
        if(item->nextItem != NULL)
            item->nextItem->previousItem = newItem;
        item->nextItem = newItem;
    }
    return newItem;
}

/*
 * Removes a ListItem from the linked list and free() the memory formerly used by said ListItem.
 *      - Does not free the data pointer, but rather returns it
 *      - If passed a pointer to NULL, function returns NULL to signal an error
 * 
 * @param item The ListItem to remove from the list.
 * @return The data pointer from the removed item. May be NULL.
 */
char *LinkedListRemove(ListItem *item)
{
    //First, assigns the pointers for the previous and next elements to each other (need to check each case to ensure no NULL call)
    if(item->previousItem != NULL)
        item->previousItem->nextItem = item->nextItem;
    if(item->nextItem != NULL)
        item->nextItem->previousItem = item->previousItem;
    //Then, we save the data pointer to return at the end of the function
    char *temp = item->data;
    //Finally, we free the memory pointed to by *item and assign *item = NULL. If *item == NULL, return NULL to signal an error
    if(item == NULL)
        return NULL;
    free(item);
    return temp;
}

/*
 *  Returns the total size of the linked list that contains the ListItem, whether or not
 *  the ListItem is at the head of the list
 * 
 *  @param list An item in the list to be sized.
 *  @return The number of ListItems in the list (0 if `list` was NULL).
 */
int LinkedListSize(ListItem *list)
{
    //if list is NULL, return a 0 since the list is empty
    if(list == NULL)
        return 0;
    ListItem *temp = list;
    int ListSize = 1;
    //If the list item is not at the head of its respective list, move the temp pointer to the head
    while(temp->previousItem != NULL)
        temp = temp->previousItem;
    //now move the temp pointer back across the Linked List, counting up for each increment starting at 1
    while(temp->nextItem != NULL)
    {
        temp = temp->nextItem;
        ListSize++;
    }
    return ListSize;
}

/*
 *  Returns the head of a list given some element in the list. Returns NULL if passed a NULL pointer in the
 *  param.
 * 
 *  @param list An element in a list.
 *  @return A pointer to the first element in the list. Or NULL if provided an invalid list.
 */
ListItem *LinkedListGetFirst(ListItem *list)
{
    if(list == NULL)
        return NULL;
    ListItem *temp = list;
    //if list not already at head of list, move temp pointer up the list until it reaches the head
    while(temp->previousItem != NULL)
        temp = temp->previousItem;
    return temp;
}

/*
 *  Returns the tail of a list given some element in the list. Returns NULL if passed a NULL pointer in the
 *  param.
 * 
 *  @param list An element in a list.
 *  @return A pointer to the last element in the list. Or NULL if provided an invalid list.
 */

ListItem *LinkedListGetLast(ListItem *list)
{
    if(list == NULL)
        return NULL;
    ListItem *temp = list;
    //if list not already at head of list, move temp pointer up the list until it reaches the head
    while(temp->nextItem != NULL)
        temp = temp->nextItem;
    return temp;
}

/*
 *   Switches the data pointers of the two ListItems in the parameter.
 *       -Returns an error if either ListItem is NULL
 *       -Data pointers are still switched even if one or both are NULL
 * 
 *  @param firstItem One of the items whose data will be swapped.
 *  @param secondItem Another item whose data will be swapped.
 *  @return SUCCESS if the swap worked or STANDARD_ERROR if it failed.
 */
int LinkedListSwapData(ListItem *firstItem, ListItem *secondItem)
{
    //if either ListItem pointer is NULL, return an error
    if(firstItem == NULL || secondItem == NULL)
        return STANDARD_ERROR;
    char *temp;
    //Switch the two data pointers through the use of an additional temp pointer
    temp = firstItem->data;
    firstItem->data = secondItem->data;
    secondItem->data = temp;
    return SUCCESS;
}

/**
 * LinkedListPrint() prints out the complete list to stdout. This function prints out the given
 * list, starting at the head if the provided pointer is not the head of the list, like "[STRING1,
 * STRING2, ... ]" If LinkedListPrint() is called with a NULL list it does nothing, returning
 * STANDARD_ERROR. If passed a valid pointer, prints the list and returns SUCCESS.
 *
 * @param list Any element in the list to print.
 * @return SUCCESS or STANDARD_ERROR if passed NULL pointers.
 */
int LinkedListPrint(ListItem *list)
{
    if(list == NULL)
        return STANDARD_ERROR;
    ListItem *temp = LinkedListGetFirst(list);
    printf("[ ");
    int newLineCounter = 0;
    while(temp != NULL)
    {
        printf("%s, ", temp->data);
        temp = temp->nextItem;
        if(newLineCounter++ == 8)
        {
            printf("\n");
            newLineCounter = 0;
        }
    }
    printf("]\n");
    return SUCCESS;
}

