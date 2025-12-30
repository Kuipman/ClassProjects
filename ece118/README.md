# ECE-118: Mechatronics

Class Description:

>Technologies involved in mechatronics (intelligent electro-mechanical systems) and techniques necessary to integrate these technologies into mechatronic systems. Topics include electronics (A/D, D/A converters, opamps, filters, power devices), software program design (event-driven programming, state machine-based design), DC and stepper motors, basic sensing, and basic mechanical design (machine elements and mechanical CAD). Combines lab component of structured assignments with a large and open-ended team project. Students who enrolled in this class will learn how to solve engineering problems using the C Programming Language

This course is widely-regarded as the toughest engineering course at UC Santa Cruz, and for good reason: the demand for this course is significantly higher with fast-paced lab assignments in a variety of fields including circuit design, embedded software design, mechanical engineering and fabrication, and the capstone project for this course (designing a small autonomous robot from scratch) leverages each of these aforementioned fields. As such this course has the largest unit count at UC Santa Cruz at 10 units versus the standard 5 units.

The lab assignments in the Projects/ folder here only comprise the programming sections of this course, and are each briefly described below.

Note: For size and complexity considerations the capstone robot project for this course (nicknamed "The BOAT") has been separated into a separate repository.

## Lab 0: The Cockroach

Programming our first robot: a small, two-wheeled bot operated by a PIC32 development kit. Programming this leverages the event service framework, an important principle in robotics, used by this class for all programming labs. Here, we explored the basics of event checkers, test harnesses, finite state and hierarchical state machines.

Additionally (not included here), this lab exercised basic soldering skills with a small circuit board.

## Lab 3: Motors

This involves building a driver for DC motors, servos, and stepper motors, both directly using an H-bridge (see the L298n, for example) as well as using a dedicated driver board (built by staff at UC Santa Cruz). This lab also includes ways to mitigate and snub inductive feedback.