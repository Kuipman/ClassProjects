Name: Nicholas Kuipers


Part 1 Prompts:
---------------------------------
valsToBeSorted element values:

139
38
208 
50
56

---------------------------------
Line numbers where changes were made:

12 - 15 	(condensed to 12)
14 		(condensed)
18 		(additional comment added)
22 - 23  	(condensed to 20)
30		(condensed)
35		(condensed)

---------------------------------


=======================================
Lab 1 Retrospective:

	For this lab I engaged in a series of fundamental exercises in using
Git, MPLAB, and the C language that will serve as building blocks to draw upon
when working with future labs in the course (this lab also had some steps regarding
setup and work with the UNO32 board, however I ran into several problems with the
hardware that I will discuss in a moment). This project had me compose a basic 'Hello World'
program that outputs a string of text to the console (in this case the simulator) and 
learn to build and run the program within the MPLAB suite. After some practice with Git 
commits to my project hub I then moved into practice with debugging and formatting a 
set of code that was provided to me. Here I worked with the debugger feature and breakpoints, 
which are invaluable in just about any IDE for decyphering potential issues with your code.
	From here I worked with another set of provided code to practice my hand more directly
with the C language itself. Here, the code provided a Celsius to Fahrenheit calculation, and I
was asked to adjust the output format (through headers, # of decimals, etc) of this code, then 
create a second calculation of Kelvin to Fahrenheit that would output in the same format as 
the first calculation. 
	I made as much progress as I could in part 3, however with the issues I experienced with
the UNO32 (which I will address shortly) I was not able to verify whether my code for this part
would properly output onto the board. The code properly compiled and no error messages were displayed,
however I cannot properly confirm that the board will perform the desired operation.

	For the most part this lab went fairly straightforward. Having prior experience with Gitlab
and the C language were major assets here, however the greatest challenge I faced was in my
(thus far failed) attempts to get the PIC32kit to connect to my computer. The CoolTerm software
was not able to recognize any serial ports on my computer, despite my verification via Device Manager
(Windows) that my computer in fact has two active serial ports. Furthermore, upon connecting the PIC32
device to my computer I am not reading any discernable change to my port status (the LEDs on the devices
ARE lighting up but there is no further indication of a connection). I have spent a good deal of time
(probably more than what I spent on the rest of the lab at this point) researching ways to fix this
issue, however this does not seem to be a common problem OR I'm simply unlucky in finding the right
information. Either way, this remains to be an issue that I hope to get some help from a TA with soon.
I did ask some questions on the discussions board and sent out an email, but no proposed solutions have
worked as of yet so this will likely be a lab hours issue.

	All in all the lab is fairly straightforward and a good introduction to the environment we're
going to be working with for the duration of the quarter. Due to elements outside our control lab hours
did go remote, which I think is a major problem due to the amount of difficulties a fair amount of the 
students are initially having with simply getting hardware/software to run on their systems, let alone building
and compiling their code once their systems do function as needed. I think especially in the first couple
weeks as students are trying to familiarize with the particular IDEs and hardware needed for the course
they need more direct support from a TA physically present to see and fix the problems first-hand.
But again, elements outside our control prevented this from happening.
