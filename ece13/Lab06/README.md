#Lab 06

Name: Nicholas Kuipers

ID: 1899399


1. Lab Summary:

	For this lab I worked directly with the PIC32 and microprocessor hardware to interact
with direct input/output devices located on the chipkit, including its buttons, switches, potentiometer,
and OLED display. These systems utilize ISRs (Interrupt Service Routines) and timers heavily,
and this lab gave valuable insight into how these interact and connect within the system and
how they can be manipulated. More specifically, this lab focused primarily on reading output from
the chipkit and manipulating peripherals on the chipkit to produce different outputs.


2. Approach:

	My approach to this lab involved a fairly dense amount of research into the PIC32 architecture and
techniques such as bit masking. This lab was a sharp departure from the themes of the prior labs in this class
and required a fair amount of new methods to fulfill the requirements. After a fair amount of research into these
categories I laid out my methods for each part of the lab and constructed them one by one.
	Understanding the exact syntax required to activate and interact with each port of the device was 
a challenge that took some time, but became significantly easier to work with once I managed to make the
ports work. With each part of the lab, I started with a simple few lines of code in my main() function to ensure
I understood how these ports interacted and the peripherals produced the desired results (i.e. a switch turns on
an LED, a button turns an LED on/off, etc). 
	NOTE: make sure you use a heap when you test my part 3, as I use malloc().
	A problem I encountered was in part 3, where I initially had my values for percentage and potentiometer
value aligned to the left. This created a problem where as the values grew larger and then smaller there were "left
over" digits that would stay behind (i.e. the percentage would show as 9%%). After reviewing the demo video for
this part I realized the digits were right-align formatted, and after making the appropriate changes my lab
worked as intended.
	

3. Results:

	I accomplished parts 1 - 4 and each part works as intended. I spent roughly 10 hours on this lab given
the more rigorous need for research and planning compared to previous labs. I liked the transition to working with
direct hardware and was thrilled to be working with peripherals, however I felt the lab report was vague in certain
areas and information (especially regarding syntax) was vague so I feel I used a lot of extra time in simply finding
port information that could have been spent better designing my algorithms. But it's a mild criticism.
	
	