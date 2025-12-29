#Lab 07

Name: Nicholas Kuipers

ID: 1899399


1. Lab Summary:

	For this lab I worked directly with the microprocessor hardware to interact with the buttons and potentiometer
physically located on the board, along with the OLED display to simulate an oven interface (complete with an
oven animation). This project relies heavily on the foundation built in lab 6 with the use of ISRs (Interrupt Service
Routines) and several timers. This project also introduced the use of a state machine, a highly-useful program structure.

2. Approach:

	My approach to this lab involved a fairly long amount of planning, as the implementation of a state machine
requires care and proper foresight into the functions and transitions involved with each state. After a fair amount of
preparation I organized my code into a series of modules, which I proceeded to implement in the program itself. The 
result was a large amount of helper functions that carried out simplistic functions and worked together to create 
a finished product.
	I ran into an issue with implementing ASCII characters onto the board, and even with the help of a TA
I was unable to project the required ASCII characters for the oven. For some reason my board would not recognize
any ASCII values above 127 (no special characters), so it would display boxes (or just not work at all). My
placeholder code is a series of equal signs for the oven top/bottom not cooking and ~ signs to simulate the top/bottom
cooking, and since I was unable to make my ASCII characters work properly these placeholders are in place in the 
final product.
	Implementing the state machine wasn't actually too much trouble; since the diagram was provided the blueprint
was essentially right in front of us. I simply made a series of conditional statements for each state that compensated
for each desired situation and dictated the traits of the state transitions. Conversely, getting my buttons and
potentiometer to work took some time.

3. Results:

	I completed the lab (minus extra credit), and each portion works as intended. This lab was indeed more involved
than previous labs, and I easily spent 15-20 hours planning and carrying out this lab. I enjoyed working with a state machine
and implementing a basic version; I've worked with them before and have found them an excellent way to organize a program
and simplify the execution of each aspect of the program. This also drew heavily from Lab 6, and I found myself referring
back to my code from that lab often throughout the course of implementing my design.
	
	