# ece121: Microcontroller System Design

Class Description:
>Focus is on the design and use of microcontroller-based embedded systems, specifically addressing issues of low-level functionality, direct manipulation of input/output using various specialized peripheral sets, and multiple communications protocols. Covers timers, Input Capture, Output Compare, ADC, PWM, interrupts, bus and memory organization, DMA, SPI, I2C, device driver programming, serial packet communication, and clocking. Students enrolled in this class learn how to use the C programming language to solve engineering problems.

This class was a deep-dive into bare-metal C engineering on embedded systems, covering datasheet analysis to reporting to writing extensive C libraries interfacing with device hardware peripherals (timers, ISRs, buttons, UART/SPI/I2C), to writing optimized code for resource management, to project documentation and reporting.

This was also one of my two favorite classes in my undergraduate career, the other being ECE118.

The individual labs are described below.

## Lab 0: Startup

Relatively simple project testing the code-flashing pipeline for the PIC32 development kit. This creates an 8-bit free-running counter using a hardware timer, and 8 LEDs on the I/O shield are lit and dimmed respectively for each bit value in the counter.

## Lab 1: Serial Device Driver and Protocol Communication

This lab is separated into three parts:

1) Initialize the UART serial port on the PIC32 (verified with successful echo of data sent from laptop to PIC32)

2) Write (and test) a UART full-duplex interrupt driven RX/TX serial device driver

3) Write an application using this device
driver library to send and receive data bytes over the serial link to demonstrate basic functionality of
your device driver.

This lab is the first real forray into exercising actual embedded engineering principles in designing and developing an actual communications protocol that would be used to interface with an embedded system. Before a single line of code could be written this required extensive research into UART and communications protocols to understand the packet structure required for the design and how to leverage the UART peripheral on the PIC32 for transmitting and receiving these packets. Learning to read a user manual and datasheet for a development kit was essential for incorporating this design onto the PIC32 specifically. and referencing the PIC32 datasheet to interact with its interrupt protocols and UART peripheral.

The UART driver and packet protocol built in this lab are intended to serve as the baseline for the remainder of coursework in this class, including Lab 2.

## Lab 2: R/C Servo, Rotary Encoder, and Pulse Width I/O

This lab builds upon the communications protocol from Lab 1 to allow for an interface with a Python application on a laptop. This application serves to drive a series of motors, which requires a separate series of drivers to interact with an R/C servo via Pulse Width Modulation (PWM). The Python program activates the motors and drives them a particular direction, while a rotary encoder peripheral (attached to the PIC32 I/O shield) dictates the speed at which the motors spin.