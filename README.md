# Snake Game in C++

This project contains different versions of a simple Snake game written in C++ for the console.

## Project Structure

The project is divided into three parts:

- **Part A**: Snake implemented using arrays
- **Part B**: Snake implemented using vectors
- **Part C**: Snake implemented using a linked list

Each version keeps the same general game logic:
- the snake moves inside the console window
- the player controls the direction
- the snake eats fruits to grow
- the score increases when a fruit is eaten
- the game ends if the snake collides with itself

## Requirements

This project is designed for **Windows** because it uses:

- `conio.h`
- `windows.h`

You need a C++ compiler such as:

- **MinGW g++**
- or **Visual Studio C++ compiler**

## How to Compile and Run

### With g++

Open **Windows Terminal** or **Command Prompt**, go to the folder containing the source file, then run:

```bash
g++ snake.cpp -o snake.exe
.\snake.exe
