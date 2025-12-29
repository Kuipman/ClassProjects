# ECE 121 Lab 1 - Nicholas Kuipers 1899399

## Overview 

Using the PIC32 Microcontroller, create a functional UART driver library that utilizes a circular buffer for each of the bi-directional pathways (receive/transmit). UART driver will utilize RX/TX interrupts to facilitate immediate responsiveness to asynchronous data received from a user, and synchronous data to be transmitted by the system.

From there, create a protocol library that interfaces with a python "hub" application by creating an encoding/decoding algorithm that builds data packets to send to a python application and decodes data packets (of the same construction) from the application.

The lab is organized into three parts, which will be discussed separately below.

## Part 1

Part 1 illustrates a basic understanding and initialization of the UART driver on the PIC32 via a program that writes data from the UART's Receive Hardware Buffer to its Transmit hardware buffer (henceforth referred to as the RX FIFO and TX FIFO, respectively). The result is a program that echos received characters back to the user's serial terminal (i.e. CoolTerm, TeraTerm, etc).

TestHarness.c comprises the quality-control aspect of this lab and serves to illustrate the functionality of parts 1 and 2 of this lab.

## Part 2

Part 2 illustrates the functionality of the software circular buffers (henceforth referred to as RXBUF and TXBUF, referring to the respective FIFOs they are attached to), and the functionality of the UART1 RX and TX interrupt protocols.

# RX Interrupt

The RX Interrupt is triggered when the RX FIFO has data available to read. The entirety of receive logic (given its asynchronous nature) is handled in IRQ_Handler_UART1_RX() , in UART.c. This first performs error-checking on the received character in U1RXREG (this register points to the first available character in the RX FIFO). 
	- For a FIFO overrun (OERR bit), attempts to pull all data in the FIFO to RXBUF. If RXBUF is or becomes full, the remaining characters in the RX FIFO are discarded.
	- If a Frame Error or Parity Error are found (FERR, PERR), the character is discarded.

If the received character passes error checking, it is placed into RXBUF. If RXBUF is full, the character is discarded instead. The RX IRQ flag is then cleared. If additional characters are present in the RX FIFO, the flag will automatically be set again and the function will be again performed for the next character in the FIFO.

The RX Interrupt is always active.

# TX Interrupt

The TX Interrupt is triggered and asserted when all characters have been transmitted from the FIFO. The function IRQ_Handler_UART1_TX() handles the TX IRQ logic.

The TX Interrupt is initially NOT active. It is activated through normal, non-IRQ involved operations: for purposes of Lab 2 it is activated via the main() function once the RXBUF is full from user input, and its contents are moved to TXBUF for re-transmission. (Future implementations will make use of putchar() in activating the TX IRQ, since putchar() will send a character to the TXBUF for transmission.)

For part 2, when the TX Interrupt is active 

//////////////////////////////////////////////////////////////

The TX Interrupt is triggered when there is at least one empty space in the TX FIFO. The function IRQ_Handler_UART1_TX() handles the TX interrupt logic.

The TX Interrupt is initially NOT active. It is activated through normal functionality in the main() function where it is activated by a check of whether the TXBUF has available data. The putchar() function will also have a separate logic for activating the TX IRQ. The TX IRQ is deactivated in its IRQ handler when the TXBUF is empty. Due to the available IRQ options (set in U1STA), this method of activating and deactivating the TX IRQ is the simplest method for sending synchronous transmissions while allowing the rest of the system to otherwise function normally without a runaway IRQ. 

In the __IRQ function called by the UART1 IRQ vector, the TX interrupt will have a lower priority (via an if-else if statement) than RX, so if both RX and TX flags are set the RX protocol will run through everything in the RX FIFO first before the TX protocol can begin its own protocol.

# main()

The first test harness for part 2 tests circular buffer functionality and operates somewhat similarly to part 1:
- Asynchronous data is sent from the user's serial terminal.
- The RX interrupt is called and sends a character from the RX FIFO into the RXBUF. This cycle is repeated while the RX FIFO has available data. Any data beyond 16 characters is discarded. 
- the main() function checks if there is data in the RXBUF. If so, a test function is called (specifically for test bench purposes) that sends available RXBUF data to the TXBUF. The TX interrupt is activated.
- The TX interrupt is called and pulls a character from the TXBUF into the TX FIFO (via GetChar). This cycle is repeated while TXBUF has available data and the TX FIFO is not full. If the TX FIFO is full, the IRQ flag will remain set and the cycle will loop (without pulling data from TXBUF) until there is available space in the TX FIFO. Once TXBUF is empty, the TX interrupt is deactivated.


TestDataNumber1TestDataNumber1..TestDataNumber1TestDataNumber.1...
TestDataNumber1TestDataNumber1..TestDataNumber1TestDataNumber.1.
TestDataNumber1TestDataNumber1..TestDataNumber1TestDataNumber.1.



