#Lab 09

Name: Nicholas Kuipers    1899399
      Luca Altaffer       1686640

MY REPO CONTAINS THE FINAL VERSION OF THE PROJECT

I wrote:
	Message.c
	Field.c
	AgentTest.c
	NegotiationTest.c

The Field AI kicks the staff AI's butt at least 55% of the time,
humbly request extra credit in exchange for the roughening.


1. Overview:

	The BattleBoats system is comprised of a large series of modules that interlink to create a simulation of a 
battleship game on the PIC32 microprocessor. The system is mainly ran by the Agent.c state machine, and the overall
game is conducted based on the current state/state transitions experienced by the machine. The game starts with a Negotiation,
which makes use of hash functions and random number generation to simulate a "coin flip" to determine who goes first (this also
comes with cheat detection and an option to include the capability to attempt cheating). From here the "board" is created with each
player generating two fields on which to play the game: one field houses their own ships while the other tracks the unknown and known
spaces of the enemy field.
	The game is played via each player sending messages back and forth to each other using the NMEA0183 protocol, which is structured
with a start delimiter, a payload, a checksum, and an end delimiter. The Message.c function is responsible for encoding information into messages
that can be sent to the other player, as well as parsing and decoding received messages so the player can easily use the information in the game.
	The game continues with each player taking turns "firing" at unknown spaces on their opponent's board until one player loses all four of their
ships. At that point, the state machine shows an end screen and the game ends.

2. Approach:

	Myself and Luca had 8 modules to write, so we split them into two sets of 4 that seemed evenly balanced. We checked in daily and spent time
looking over each others' code, but for the most part we worked indepently and combined our code at the end. In hindsight we should have spent more
time combining our code and ensuring all the modules were compatible so we could spend more time debugging problems rather than focusing on what
test benches (written by humans) said.
	A testing strategy I found effective for my Message.c file was in running through many different messages through each function that were 
both valid and invalid, of all different types, and ensured respective error codes were cast. 
	After a great deal of debugging Message.c, Field.c, and Negotiation.c work as intended. Unfortunately, no matter how much we've panned over the code
Agent.c still has a bug that prevents the game from starting. Currently, with the inclusion of that file the two PIC32s will sit for a moment (when START is pressed),
then both will show a fatal error. When this file is removed and the correct object file placed in its stead, the game runs to completion.

3. What I've Learned:

	That programming a simple game of Battleship is an absolute endeavour.
	
	On a more serious note, organization played a huge role in this. This lab was simply massive compared to the other labs that came before, and taking a step back
periodically and taking time to plan really saved me a lot of time in implementing my design ideas in getting my respective files working. Debugging also played a huge
factor (though MPLAB really struggled in performing with this one), and I probably spent close to 30 hours on writing and debugging this lab. Overall, this taught me
a great deal of new methods to implement in future projects and I'll be saving this code to look back on long into the future.
	
	