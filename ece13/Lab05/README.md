#Lab 05

Name: Nicholas Kuipers

ID: 1899399

1. Timing Experiment Results:
	
	SelectionSort() = 39.179ms

	InsertionSort() = 24.496ms

	This was expected due to the nature of each method of sorting. SelectionSort() will generally
engage in a great deal of redundant actions, since for each list item (from left to right) it cycles
through and checks every list item to the right of the selected item before the next item is selected. 
As the list to sort grows longer, the amount of redundant checks also increases at a close to 
exponential rate.
	Compare this with InsertionSort(), which operates by selecting an item and maneuvering across a
second list for the proper position to insert it. While redundant actions still occur with this method, this removes
the need to check every list item for every selected item, which (depending on the size of the list to be sorted)
can dramatically reduce the amount of time spent sorting.

2. Lab Summary:

	This lab asked me to create a library to create and interact with Linked List data structures, then utilize these
lists to implement two list sorting methods and compare the efficiency between the two methods. Proper utilization of pointers
and references were instrumental in implementation of this lab, given how Linked Lists rely predominantly on pointer variables to
allow for easier manipulation and transfer of these values. Another important focus in this lab was the prevalence of
sorting algorithms in computer science and how data structures such as linked lists can be utilized
to perform sorts efficiently.

3. Approach:

	My first point of contact to this lab was in reading the lab manual and making detailed notes about what was
overall expected of me. The manual provided hints and recommendations in how to approach certain tasks and organize certain
functions in LinkedList.c and for the sorting algorithms, which were most helpful. From here I shifted focus into a combined effort of
building my functions in LinkedList.c and building my test bench for my file. As I constructed each function, I built a series of tests
in the test bench to ensure the function works (and debug/fix it if necessary) before moving onto the next function. Overall this
process went fairly smooth and I didn't encounter many difficulties in this portion of the lab.
	Once my LinkedList.c and test bench were built and fully functional, I moved over to sort.c and building the respective sorting
algorithms. Again utilizing the information presented in the lab manual, I utilized my notebook to sketch out my basic algorithms
for SelectionSort() and InsertionSort(), and from here implementing these to their respective functions went fairly straightforward. Some
debugging was needed for InsertionSort() (my strcmp ended up being backwards) but once that was solved my final step was testing both 
functions with the MPLAB stopwatch.
	My final issue with the lab came at the very end after I had taken down the values. My LinkedListPrint() function would print the first
set of values without issue, but once a new unsorted list was created and sorted my print function ended up getting locked in a loop and would not
function. After some debugging I found the list had somehow attached its head to its tail, locking my embedded LinkedListGetFirst() in my print function
into a forever loop. My fix ended up being the addition of setting the previous and next pointers in my LinkedListNew() function to NULL, which
I did not anticipate would be a problem and what I missed in my test bench.
	I feel my approach to this lab was fairly solid, and the lab went fairly smooth. My only fix would be to make the addition of setting those pointers
to NULL as mentioned above, to avoid the extra 30+ minutes spent debugging my print function.

4. Results

	The lab works well and in accordance to to what is required in the lab manual. Overall, this took me a cumulative 5 hours to pore over the
lab manual, design and implement each algorithm for LinkedList.c, write out each test for the LinkedList test bench, and design and implement the
algorithms for each of the two sorting methods in sort.c. I feel this is a solid lab that does well to test our understanding of pointers, and I don't
have any issue personally with any aspect of it.
	