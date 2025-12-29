#Lab 08

Name: Nicholas Kuipers

ID: 1899399


1. Lab Summary:

	For this lab I stepped away from the MPLAB and microprocessor environments and conducted a purely coding project
in Visual Studio. This project relies greatly on using static variables/structs and pointers to maneuver from one part
of memory to another in order to access files from a folder and store their values in reliable areas that are easy to access.

2. Approach:

	My approach to this lab, as with the past several labs, included a fair amount of planning as organizing a system
that opens a file and pulls one character of information at a time from it to store in a specific location takes time
to properly implement. Using a static struct declared at the beginning of a .c file was unfamiliar territory for me, and 
my early planning did not account for this workaround and instead involved significantly more complex solutions that
would have taken me far more time to implement and likely caused the program to run significantly slower. Thankfully, 
after some elaboration I was able to dramatically simplify my approach to this lab.
	My first implementation of the inventory system did not work as intended given my int array is required to store
item values between 0 and 255, however the array initialized with all zeros. This facilitated a solution of an array pointer, which
initially "points" to the first element of the array and moves to the right as the array is filled with the AddToInventory() function
until it reaches the end of the array. This proved a significantly simpler implementation and works like a charm
	The most time consuming portion of this lab was in implementing the helper function in Game.c that would open an indicated file and
read each character of the file, performing respective actions as needed (checking inventory for addition of an item, checking if
the current description of the room is allowed given the current items in inventory, etc). Once this function worked, the rest of the
functions in Game.c worked as intended since the majority of them required some method of opening and reading a file.	

3. Results:

	The lab works as intended. I am encountering a unique issue with room27.txt, in which it is entered from the North exit and the description
states there is an East entrance, however all four exits are marked as available. Upon debugging I found the north exit fills normally (goes back to room30.txt), 
however the remaining 3 exits are filled with a '255' value. Given this does not occur with any other room I've found thus far in playing the game, I feel comfortable
in making the claim that there is an error with the room27.txt file. 
	I spent a good deal of time (15-20 hours) on this lab and rather enjoyed it. This lab was significantly different than prior labs and had an element of fun to it, especially
when the code began to work and I was rewarded with a (nearly-functional) game.
	
	