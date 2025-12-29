# ece13: Computer Systems and C Programming

Class Description: 
>Computer Systems and C Programming is intended to bring students up to speed on programming small and large programs in C. Originally written in 1978, C remains the most popular programming language, and the most used one in terms of numbers of computer programs written in it. The course approaches C from an embedded paradigm, and all programming assignments are on a 32-bit embedded micro, the Microchip PIC32. Students learn how to program in C, how to write modular code, and some of the tips and tricks when dealing with an embedded micro.

This course was my first forray into embedded systems programming using the PIC32 development kit ([not this specific one but close](https://www.digikey.com/en/products/detail/microchip-technology/EV16W43A/21803091)). A total of 9 lab assignments were assigned that covered everything from building a basic C executable (using make) and flashing to the devkit to interfacing with the various devkit peripherals to eventually creating a BattleBoats game AI that successfully beats the classroom staff AI.

The individual labs are briefly described below. They are described in further detail in their individual directories.

## Lab 1: Compiling, Running, and Debugging

This lab is effectively what the title says: we build the pipeline for flashing code to the PIC32 devkit and debugging in the MPLAB X IDE.

## Lab 2: Calculator

A simple calculator that is interfaced with via the devkit's serial port. This has a variety of available operations including averaging, degree conversions, and float rounding.

## Lab 3: Matrix Math

A matrix math calculator for performing operations on NxM matrices. These include matrix and scalar multiplication, traces, transposes, and determinant calculations.

## Lab 4: Reverse Polish Notation

Another calculator that parses Reverse Polish Notation strings using a stack data structure.

## Lab 5: Linked Lists

Uses pointer arithmetic to manually create a doubly-linked list data structure.

## Lab 6: Basic IO on a Microcontroller

Introduction to hardware peripherals of the PIC32 devkit, including the hardware timers, Interrupt Service Routines, and the various switches and buttons on the I/O shield.

## Lab 7: Toaster Oven

Simulation of a toaster oven using timer interrupts, finite state machines, and an event control framework.

## Lab 8: Role-Playing Game

Playable dungeon-crawler game through accessing a file directory containing information on a series of rooms and their descriptions.

## Lab 9: BattleBoats

Develop libraries and agents necessary for a two-player game of BattleBoats (resembling Hasbro's Battleship game). Two PIC32 boards are connected via UART for gameplay. Additionally, develop an AI agent that can play against another agent or a human player. This agent must be able to defeat the classroom staff AI agent in more than 55% of simulated matches.