# ECE 121 Lab 0 - Nicholas Kuipers 1899399

## Overview 

Using the PIC32 Microcontroller, create an 8-bit counter that increments sequentially every 250ms and resets when the counter reaches the value 255 or a button is pressed. This project makes use of the I/O shield of the PIC32: the 8 embedded LEDs display the 8-bit counter's current value, and the buttons each perform the same function of resetting the timer *upon button press* and not upon button release.

## Plan of Attack

Program first initiates all LEDs and buttons (driving them low), and then initiates the loop counter. Using a NOP loop, the while loop embedded in main.c will cycle approximately every 250ms. On every loop repetition the counter's current value is first written to the hardware LEDs. Then, the counter is incremented and the program checks its reset parameters for either a button press or the counter reaching 255. If a reset parameter is true, the counter is reset and the LEDs are deactivated to reflect a 0 until the counter is incremented again. Otherwise, the NOP loop is reached, wherein the code is delayed for 250ms while the reset parameters (namely the button press) are checked every 5ms and acted upon accordingly if a button is pressed.

## Lab Organization

A resource folder was added to the repository for Lab 0, which contains the pseudocode and block diagram for this project. NOTE the block diagram is out-of-date and contains old function names, but still displays the overall logic for this lab.
