# Producer-Consumer Problem Implementation
## Table of Contents
- [Introduction](#introduction)
- [Problem Description](#problem-description)
- [Project Goals](#project-goals)
- [Tools and Techniques Used](#tools-and-techniques-used)
- [How to Run the Program](#how-to-run-the-program)
- [Code Explanation](#code-explanation)
- [Program Output](#program-output)
- [Conclusion](#conclusion)
- [References](#references)
  
## Introduction
This project is a simple implementation of the Producer-Consumer Problem, which is one of the classic problems in the field of concurrency. The goal of this project is to manage the production and consumption of data in a shared memory (buffer) using concurrency tools. This implementation is done using the C++ programming language and Windows operating system libraries.

## Problem Description
In the Producer-Consumer Problem:
- The producer generates data and places it in a shared buffer.
- The consumer reads and consumes the produced data from the buffer.
- The buffer has a limited capacity, and it is necessary to prevent it from being overfilled or emptied excessively.
- Production and consumption operations should not be performed on the buffer simultaneously.

## Project Goals
1. Manage concurrency between multiple producers and consumers.
2. Prevent race conditions when accessing the buffer.
3. Ensure the orderly production and consumption of data.
4. Implement concurrency mechanisms using the following tools:
   - **Semaphore**: To manage the number of empty and full slots in the buffer.
   - **Critical Section**: To prevent simultaneous access to shared variables.
   - **State Management**: To ensure sequential execution of production and consumption.

## Tools and Techniques Used
1. **Semaphore**:
   - Two semaphores named `empty` and `full` are used:
     - `empty`: Controls the number of empty slots in the buffer.
     - `full`: Manages the number of full slots in the buffer.
2. **Critical Section**:
   - Used to control simultaneous access to shared variables (e.g., buffer, indices, and state variables).
3. **State Management**:
   - A boolean variable named `is_producer_turn` is added to precisely control the turn of production and consumption.
4. **Circular Buffer**:
   - An array with `in` and `out` indices is used to manage the buffer space.
5. **Random Delays**:
   - Random delays are used to simulate real-world production and consumption operations.

## How to Run the Program
To run the program, three arguments are passed to it:
1. **Program execution time (seconds)**: The duration for which the program will run.
2. **Number of producers**: The number of producer threads.
3. **Number of consumers**: The number of consumer threads.

### Example:
1. Compile the code using a Windows compiler like MinGW:
   ```bash
   g++ producer_consumer.cpp -o producer_consumer.exe -lws2_32
   ```
2. Navigate to the executable file's directory:
   ```bash
   cd C:\Projects\producer_consumer
   ```
3. Run the program:
   ```bash
   .\producer_consumer.exe 10 2 3
   ```
   In this example:
   - The program runs for 10 seconds.
   - 2 producers and 3 consumers operate concurrently.

## Code Explanation
### Main Structure of the Code
1. **Shared Variables**:
   - Circular buffer and `in` and `out` indices for storing data.
   - Semaphores and Critical Section for managing concurrency.
2. **Main Functions**:
   - `insert_item`: Adds data to the buffer by the producer.
   - `remove_item`: Removes data from the buffer by the consumer.
   - `producer`: Function executed by the producer.
   - `consumer`: Function executed by the consumer.
3. **State Variable**:
   - The `is_producer_turn` variable is used to control the turn of production and consumption.

### Program Execution Flow
1. **Producer**:
   - Waits for an empty slot in the buffer.
   - Produces data and places it in the buffer.
   - Changes the turn to the consumer.
2. **Consumer**:
   - Waits for a full slot in the buffer.
   - Reads and consumes data from the buffer.
   - Changes the turn to the producer.
3. **Turn Control**:
   - Production and consumption are only performed when it is their turn.

## Program Output
The program output will be as follows:
```
Producer produced: 42
Consumer consumed: 42
Producer produced: 17
Consumer consumed: 17
Producer produced: 56
Consumer consumed: 56
Terminating the program...
```
The output shows the sequential production and consumption of data.

## Conclusion
This project demonstrated how the Producer-Consumer Problem can be solved using concurrency tools available in the Windows operating system. The implementation successfully prevents race conditions and manages production and consumption operations in an orderly and concurrent manner. This method is particularly useful in systems with limited resources, such as embedded systems.

## References
1. **An Example Implemention for Producer-Consumer Problem**:
   - [GitHub Repository](https://github.com/forestLoop/Learning-EI338/blob/master/Project-5-2/buffer.c)

2. **Educational Resources**:
   - [Operating System Concepts (10th Edition)](https://www.os-book.com/OS10/slide-dir/) - For foundational concepts on concurrency and resource management in operating systems.

3. **Use of Artificial Intelligence Tools**:
   - Used AI tools like GPT for assistance in analyzing, documenting, and enhancing the project development process.

