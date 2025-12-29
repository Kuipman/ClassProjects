/*
 * File:   AgentTest.c
 * Authors: Luca Altaffer taltaffe@ucsc.edu
 *          Nicholas Kuipers
 *
 * Created on March 10, 2022, 9:46 AM
 */

#include "xc.h"
#include "Agent.h"
#include "BOARD.h"
#include <stdio.h>

int main(void)
{
    BOARD_Init();

    //Begin Test Bench
    printf("Welcome to the Agent Test!\n\n");

    /*
     * Function 0: AgentInit()
     * This function is self-contained (returns void and has no parameters), so testing
     * this function can only be done via testing the remaining functions
     */
    AgentInit();

    /*
     * Function 1: AgentRun()
     * This function takes in a BB_Event struct and returns a Message struct.
     */  
    //Test 1.1: Basic test in which AgentRun() receives a BB_Event with a type (BB_EVENT_CHA_RECEIVED) and a parameter. 
    //          Note the parameter is the seed for the hash function, and the Message struct receives a different value. If the resultant Message
    //          struct reflects an ACCEPT (meaning it accepts the challenge from the opposing side), the first test is successful
    printf("Test 1.1: Testing agent run with event type challenge received.\n");
    printf("Expected return event type = MESSAGE_ACC.\n\n");

    BB_Event tester = {BB_EVENT_CHA_RECEIVED, 10};
    Message message_test = AgentRun(tester);

    if(message_test.type == MESSAGE_ACC)
        printf("Test successful! Agent run returned the expected event.\n\n");
    else
        printf("Test failed. Agent run did not return the expected output.\n\n");

    //Test 1.2: Test of AgentRun()'s Start Button. AgentRun() receives a Start Button event,
    //          --if the function returns a message with the CHALLENGE type, test is successful
    printf("Test 1.2: Testing agent run with event type start button.\n");
    printf("Expected return event type = MESSAGE_CHA.\n\n");

    AgentInit();

    BB_Event tester2 = {BB_EVENT_START_BUTTON, 10};
    message_test = AgentRun(tester2);

    if(message_test.type == MESSAGE_CHA)
        printf("Test successful! Agent run returned the expected event.\n\n");
    else
        printf("Test failed. Agent run did not return the expected output.\n\n");

    //Test 1.3: Continuation from Test 1.2, in which AgentRun() receives another BB_Event dictating that
    //          an ACCEPT message was received. Function engages in a coin flip, then if function returns
    //          MESSAGE_REV this test is successful
    printf("Test 1.3: Continuing Test 1.2 by receiving an accept message.\n");
    printf("Expecting return event type MESSAGE_REV.\n\n");
    
    BB_Event tester3 = {BB_EVENT_ACC_RECEIVED, 10};
    message_test = AgentRun(tester3);
    
    if(message_test.type == MESSAGE_REV)
        printf("Test successful! Agent run returned the expected event.\n\n");
    else
        printf("Test failed. Agent run did not return the expected output.\n\n");
    
    
    /*
     * Function 2: AgentGetState()
     * This function takes in no parameters and returns an AgentState. We can use this function
     * to further test AgentRun()
     */  
    //Test 2.1: We check the current state of the agent. From our prior interactions with the state machine,
    //the current state should be either AGENT_STATE_WAITING_TO_SEND or AGENT_STATE_DEFENDING (due to a coin flip)
    printf("Test 2.1: Beginning test for agent get state.\n");
    printf("After last call to agent run, state should be either\nAGENT_STATE_WAITING_TO_SEND or AGENT_STATE_DEFENDING.\n\n");
    
    AgentState agent_state_test = AgentGetState();

    if(agent_state_test == AGENT_STATE_WAITING_TO_SEND || agent_state_test == AGENT_STATE_DEFENDING)
        printf("Test successful! State machine kept track of current state.\n\n");
    else
        printf("Test failed. State machine did not keep accurate track of current state.\n\n");
    

    //Test 2.2: This test can diverge depending on which state we are currently in.
    /*
     *  AGENT_STATE_WAITING_TO_SEND:
     *      - BB_Event has the BB_EVENT_MESSAGE_SENT
     *      - State will transition to AGENT_STATE_ATTACKING
     *      - Message will contain the type MESSAGE_SHO along with random values for row/col (AI Guess)
     * 
     * AGENT_STATE_DEFENDING
     *      - BB_EVENT has the BB_EVENT_SHO_RECEIVED
     *      - Message has type MESSAGE_RES and parameters reflective of values for row/col
     */
    printf("Test 2.2: AgentRun() continued. Depends on which state the function is currently in.\n\n");
    
    agent_state_test = AgentGetState();
    if(agent_state_test == AGENT_STATE_WAITING_TO_SEND)
    {
        BB_Event tester4 = {BB_EVENT_MESSAGE_SENT, 10};
        message_test = AgentRun(tester4);
        if(AgentGetState() == AGENT_STATE_ATTACKING && message_test.type == MESSAGE_SHO)
            printf("Test Successful!\n\n");
        else
            printf("Test Failed.\n\n");
    }
    else if(agent_state_test == AGENT_STATE_DEFENDING)
    {
        BB_Event tester4 = {BB_EVENT_SHO_RECEIVED, 10};
        message_test = AgentRun(tester4);
        if(AgentGetState() == AGENT_STATE_WAITING_TO_SEND && message_test.type == MESSAGE_RES)
            printf("Test Successful!\n\n");
        else
            printf("Test Failed.\n\n");
    }
    
    //Test 2.3: Reinitialize the game. Ensure the state is set to AGENT_STATE_START
    printf("Test 2.3: Reinitialize the game. Ensure the state is set to AGENT_STATE_START\n");
    printf("and the values are properly reset.\n\n");
    AgentInit();

    if(AgentGetState() == AGENT_STATE_START)
        printf("Test successful! State machine kept track of current state.\n\n");
    else
        printf("Test failed. State machine did not keep accurate track of current state.\n\n");

    /*
     *  Function 3: AgentSetState()
     *  This function will allow us to test the remaining functions for AgentRun()
     */
    //Test 3.1: Basic test of AgentSetState()
    printf("Test 3.1: Basic Test for AgentSetState().\n");
    printf("Attempting to set state to AGENT_STATE_ATTACKING.\n\n");

    AgentSetState(AGENT_STATE_ATTACKING);

    if(AgentGetState() == AGENT_STATE_ATTACKING)
        printf("Test successful! State was successfully set to desired state.\n\n");
    else
        printf("Test failed. State was not successfully switched.\n\n");

    //Test 3.2: Another basic test, setting state to AGENT_STATE_ACCEPTING
    printf("Test 3.2: Second basic test, set state to AGENT_STATE_ACCEPTING.\n\n");

    AgentSetState(AGENT_STATE_ACCEPTING);

    if(AgentGetState() == AGENT_STATE_ACCEPTING)
        printf("Test successful! State was successfully set to desired state.\n\n");
    else
        printf("Test failed. State was not successfully switched.\n\n");
    
    //Test 3.3: Set state to AGENT_STATE_ATTACKING, then test that state in AgentRun()
    printf("Test 3.3: Testing state AGENT_STATE_ATTACKING in AgentRun()\n\n");
    
    AgentSetState(AGENT_STATE_ATTACKING);
    BB_Event tester5 = {BB_EVENT_RES_RECEIVED, 10};
    
    message_test = AgentRun(tester5);
    
    if(message_test.type == MESSAGE_NONE && AgentGetState() == AGENT_STATE_DEFENDING)
        printf("Test was successful!\n\n");
    else
        printf("Test failed.\n\n");
    
    //Test 3.4: Final Test: When the reset button is pressed, does the state machine revert to initial settings?
    printf("Test 3.4: Does the reset button work properly?\n\n");
    
    BB_Event tester6 = {BB_EVENT_RESET_BUTTON, 10};
    
    message_test = AgentRun(tester6);
    
    if(message_test.type == MESSAGE_NONE && AgentGetState() == AGENT_STATE_START)
        printf("Test was successful!\n\n");
    else
        printf("Test failed.\n\n");
                
                

    while(1);
}
