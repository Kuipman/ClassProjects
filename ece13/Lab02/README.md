**Lab 2
Name: Nicholas Kuipers

1: What happens if the line "scanf(" ");" executes? Why?

	When this code is called, this actually leaves a newline
character in the input buffer. This does not get cleaned up without
manual intervention, and barring this the next time a function is called
that reads from the input buffer it will immediately read the newline
character and prevent any further input at that line of code. 

	On line 41 of Calculator.c I have a line that accounts for any
potential mistypes that could leave extra characters in the input buffer.
This line essentially "uses up" any extra characters until a newline character
is found:
	while ((getchar()) != '\n');


2: In this lab, we forbid you from using printf() or scanf() inside
of certain functions.  Explain why a rule like this is useful.

	Considering how printf() and scanf() interact with the input buffer
(which does not change regardless of whatever function you may be in), you could
have a situation where printf() or scanf() utilizes something from the input
buffer that is not necessarily meant for that function. There are many more
variables to keep track of when these two functions are widespread through one's code.

3: How long did this lab take you?  Was it harder or easier than you
expected?

This lab took me around 3 hours and was around the expected difficulty. Planning and
building the logic was pretty straightforward (using switch/case statements simplified
the process), however I found myself indecisive over how to most efficiently construct
my code to catch the multitudes of potential errors (i.e. division by 0, multiple inputs, etc).
I chose not to include catch statements due to time constraints, however
I hope to do so in the future.