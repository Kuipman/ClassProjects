# ece121: Microcontroller System Design

Class Description:
>Focus is on the design and use of microcontroller-based embedded systems, specifically addressing issues of low-level functionality, direct manipulation of input/output using various specialized peripheral sets, and multiple communications protocols. Covers timers, Input Capture, Output Compare, ADC, PWM, interrupts, bus and memory organization, DMA, SPI, I2C, device driver programming, serial packet communication, and clocking. Students enrolled in this class learn how to use the C programming language to solve engineering problems.

This class was a deep-dive into bare-metal C engineering on embedded systems, covering datasheet analysis to reporting to writing extensive C libraries interfacing with device hardware peripherals (timers, ISRs, buttons, UART/SPI/I2C), to writing optimized code for resource management, to project documentation and reporting. test

This was also one of my two favorite classes in my undergraduate career, the other being ECE118.

The individual labs are described below.

## Lab 0: Startup

Relatively simple project testing the code-flashing pipeline for the PIC32 development kit. This creates an 8-bit free-running counter using a hardware timer, and 8 LEDs on the I/O shield are lit and dimmed respectively for each bit value in the counter.

## Lab 1: UART Driver

This project served as a major filter for the classroom at large -- many students were unable to complete this lab until the very end of the class.