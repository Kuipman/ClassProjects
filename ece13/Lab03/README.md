**Lab 03
Name: Nicholas Kuipers
ID: 1899399

Summary: 
 
	I thought the lab went fairly well. This was a very apt practice in utilizing references
via header files and alternative C files, divising functions to perform specific tasks (including
some functions that handled a task FOR another function such as MatrixDeterminant2x2 or my
absolute value function), as well as practice in working with 3D arrays and matrices (which are
hugely important in a wide variety of disciplines within computer science) and how to manipulate their
values using simple and concise functions.
	The lab manual was a bit vague in how the testing outputs were expected to look, however I
suspect this was to allow for greater freedom in designing our own testing templates.

Approach:

	For each function I worked through the math required to accomplish each task and designed a
simple algorithm to carry these out. The vast majority of these algorithms made use of two for loops
(one loop nested in the other) to carry over/adjust/output values from/to a matrix. This approach worked
very well, and up until my MatrixSubmatrix() function I didn't run into many problems. Once I reached the
submatrix and determinant functions I needed to spend more time on these, and with the former I had some
issues with testing since the limitations that were placed on these functions (all matrix sizes were specified
at either [3][3] or [2][2]), coupled with my inability to add functions to the .h file,
created a barrier that prevented me from using a MatrixEquals() function on the output from my submatrix
function without writing a fair amount of extra code in the main() function. Which, as it turns out, is
exactly what I ended up doing: for each test case of my submatrix function I have a separate set of two for loops
that tests each element of the 2x2 matrix against the hardcoded values that I was expecting.

Feedback:

	I spent a good deal of time on this lab (~6-8 hours), most of which was in planning my algorithms and calculating
my expected values for each test. It felt pretty arduous to have to perform so many hand/computer calculations for each 
function and hardcode so many values into my main() function so that I can ensure my function works, however I understand the
importance of ensuring your code works correctly the first time so you can be assured that it will continue to work for all
cases that you may not foresee at the time. I found calculating the Inverse especially arduous (I spent a good half hour reviewing
old class notes from my Linear Math days trying to remember how its done) and at the end of the day I've decided to forego completing that
portion of the lab due to time constraints. I'll take the half point for that.

Overall this was a good lab, I'm enjoying the increasing liberties in designing my code and hope this trend continues as the labs
continue to get more difficult.

	