**Lab 04
Name: Nicholas Kuipers
ID: 1899399

Summary:

	This lab asked me to first create a working set of functions that create the "Stack"
data structure, complete with functionalities including "pushing" values to the stack, "popping"
values from the stack, and getting certain values relating to the current status of the
stack. Using these functions, I was then asked to create a working Reverse Polish Notation
calculator, which takes numerical values first before their operators (i.e: 3 + 3 = 6 --->
3 3 +  = 6). This Reverse Polish Notation calculator makes use of a stack to store the numerical
values as they are read and calculated from user input.
	With these two sets of functions I also created two unit test documents that performed a
series of "tests" that not only ensured the functions worked correctly but returned the proper
error values when they received an incorrect input. Finally, I needed to create a proper main function
that would ask the user for a series of RPN inputs, run the RPN calculator, and then output the
result (or error code) before asking for the next series of inputs.
	The most important aspect this lab taught was how to work with pointers, a crucial aspect of
coding in C and in many other languages. With this plethora of functions working together, passing an entire
set of values from one function to another would be extremely inefficient; pointers were therefore an
important element as it allowed just one set of values to be passed (by reference) from one function to
another. These functions could interact with and even change these values if needed thanks to these passed
references.

Approach:

	I read the manual first and considered the most important steps I should take. I opted to make my
stack.c file first, since it would serve as the foundation for most of the rest of the lab and especially
the RPN calculator. After contructing this file and its respective test bench, I was able to verify full functionality
of all my stack functions. From here, I moved on to RPN.c, which proved to be a far larger challenge for me.
Twice I ended up hitting a roadblock and having to rewrite much of my code within the file; pointers are proving to 
be a weak point for me and I will need to engage in further practice with them in the future. Once I wrapped my head
around implementing my stack and pulling my input reference I was able to construct the RPN logic, however a number
of small details interrupted project completion. The newline character '\n', for instance, would populate when
a user presses the enter key, however if this key were pressed before the user hits the space my code would read the
"3\n" as an invalid token. Reconciling with that took some time.
	If I were to do this lab again, as much as it pains me to say but I would do it in MPLAB. To be frank, MPLAB
is not a good IDE and it runs painfully slow on my computer. Debugging with this software is a nightmare and parsing each line
takes 5 - 10 seconds, which adds up when your code is over 100 lines. So, I went with an alternative IDE and got most of my code
to work, however upon transition back to MPLAB something broke and my program is not running its operators correctly. Somehow it is
reading a '+' character as being over 10 characters in length, let alone the strange outputs the board is generating for seemingly
no reason related to my code. As I'm out of time I disappointingly have to turn in an unfinished lab.

	The test benches for both rpn.c and stack.c passed both sets of functions through tests in both their proper functions
and in returning the proper error codes. ProcessBackspace() worked for a primitive test but remains untested for more elaborate tests, though
I am confident the logic holds through multiple backspaces. The main() function worked like a charm in my other IDE and returns
the proper result values (or error values), however something was lost in translation when migrating back to MPLAB. Despite the frustration
I did enjoy this lab, as again pointers are a weakness of mine in C and practice in this field is much appreciated. Using the lab manual, class notes,
and Google I was able to learn a few new tricks that I'm keeping in my toolbox for the foreseeable future. While this doesn't pertain
so much to the lab, this lab did give me insight into how poor quality MPLAB and the boards can be. I'm sure with more time I could have
solved whatever on earth is causing my program to act so strangely when connected to the board, but again I'm simply out of time. I will
say I hope we can work more with the interface components of the board in the future, because otherwise it seems largely pointless to me
to work through all the extra trouble of running a program through a microcontroller when it can be ran far more effectively in the IDE.