# Conveyor Belt Control Simulator

A C++ console application that simulates the operator controls and safety systems of an industrial conveyor belt.

## Features

* Starts and stops the conveyor
* Simulates item detection and processing
* Tracks the number of processed items
* Detects conveyor jams
* Automatically stops the conveyor when a jam occurs
* Blocks startup until the jam is cleared
* Includes an emergency-stop safety lockout
* Validates operator input
* Shuts down in a safe stopped condition

## C++ Concepts Demonstrated

* Object-oriented programming
* Classes and constructors
* Encapsulation
* Header and implementation files
* Private and public members
* Conditional logic
* Switch statements
* Loops
* Input validation

## Project Structure

* `main.cpp` — Program entry point
* `ConveyorSystem.h` — Class declaration
* `ConveyorSystem.cpp` — Class implementation

## Build Instructions

Compile the program with:

```bash
g++ main.cpp ConveyorSystem.cpp -o conveyor.exe
```

Run it on Windows with:

```bash
.\conveyor.exe
```

## Safety Logic

The simulator prevents the conveyor from starting while a jam is detected or the emergency stop is active. Clearing a jam or resetting the emergency stop does not automatically restart the conveyor.

## Author

Devon Glenn
