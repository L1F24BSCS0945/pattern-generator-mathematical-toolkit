# pattern-generator-mathematical-toolkit
A C++ console-based mathematical toolkit featuring number system conversion, prime and Armstrong number checking, Fibonacci, factorial, pattern generation, matrix operations, and calculation history using Stack.

## Features

* Number System Converter

  * Binary
  * Octal
  * Decimal
  * Hexadecimal
* Prime Number Checker

  * Check individual numbers
  * Generate prime numbers up to a given limit
* Armstrong Number Checker

  * Check individual numbers
  * Find Armstrong numbers within a range
* Fibonacci Series Generator
* Factorial Calculator
* Pattern Printing

  * Right Triangle
  * Inverted Right Triangle
  * Pyramid
  * Number Triangle
  * Pascal's Triangle
  * Diamond
* Matrix Operations

  * Matrix Addition
  * Matrix Subtraction
  * Matrix Multiplication
  * Matrix Transpose
* Calculation History using an array-based Stack
* Input validation for numeric and base-conversion operations
* Menu-driven console interface

## Project Structure

```text
Pattern-Generator-Mathematical-Toolkit/
│
├── main.cpp
├── Toolkit.cpp
├── Toolkit.h
└── README.md
```

### `main.cpp`

Contains the program entry point, welcome screen, main menu, and user navigation.

### `Toolkit.h`

Contains constants, function declarations, the `HistoryStack` class, and the `MathToolkit` class interface.

### `Toolkit.cpp`

Contains the implementation of mathematical functions, pattern generators, matrix operations, input validation, and calculation history.

## Concepts Used

This project demonstrates several fundamental C++ programming concepts:

* Functions
* Classes and Objects
* Arrays
* Loops
* Conditional Statements
* Switch Statements
* String Handling
* Input Validation
* Basic Object-Oriented Programming
* Stack Data Structure
* Matrix Operations
* Number Systems
* Mathematical Algorithms

## How to Run

### 1. Clone the repository

```bash
git clone <your-repository-link>
```

### 2. Open the project

Open the project folder in a C++ compatible IDE such as:

* Code::Blocks
* Dev-C++
* Visual Studio
* Visual Studio Code

### 3. Compile the files

Make sure `main.cpp`, `Toolkit.cpp`, and `Toolkit.h` are included in the same project.

For a compiler such as g++:

```bash
g++ main.cpp Toolkit.cpp -o toolkit
```

### 4. Run

```bash
./toolkit
```

On Windows, the generated executable can be run as:

```bash
toolkit.exe
```

## Example Menu

```text
============================================================
                    MAIN MENU
============================================================
  1. Number System Converter
  2. Prime Number Checker
  3. Armstrong Number Checker
  4. Fibonacci Series
  5. Factorial Calculator
  6. Pattern Printing
  7. Matrix Operations
  8. View Calculation History
  0. Exit
============================================================
```

## Purpose

The purpose of this project is to practice and demonstrate core C++ programming concepts by implementing multiple mathematical and programming utilities within one organized console application.

## Author

**Syed Hassan Raza**

BS Computer Science
University of Central Punjab (UCP)

