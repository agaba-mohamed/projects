# Gomoku AI Bot

![Illustration](illus.png)

## Overview
This project aims to develop an AI bot for the game of Gomoku (also known as Five in a Row). The bot will compete against other bots using a 20x20 game board. The primary objective is to implement a strong AI for Gomoku using various algorithms like Min-max, Monte-Carlo, or Machine Learning.

## Technical Requirements
- The bot should be able to compile on both Windows and Linux using a provided Makefile.
- Only standard libraries are allowed; no external libraries like TensorFlow or scikit-learn.
- The program will be automatically compiled and tested against other bots.
- Each move must be made within a maximum of 5 seconds, and the bot's memory usage must not exceed 70 MB.

## Game Rules
- The game is played on a 20x20 grid.
- Each player takes turns placing a stone on the board.
- The game ends when a player has five stones in a row (horizontally, vertically, or diagonally).

## Evaluation Criteria
1. **Play to Win**: The bot must recognize and play winning moves in predefined board situations.
2. **Outsmart Local Bots**: The bot will compete against bots of varying difficulty levels, aiming to maximize the number of victories.

## Directory Structure
- All source files (excluding unnecessary files like binaries, temp files, etc.) should be included in the main directory.
- Bonus files, including any additional Makefiles, should be placed in a directory named `bonus`.

## Communication Protocol
The bot must comply with the communication protocol, especially the Mandatory commands part, for seamless interaction with other bots.

## Conclusion
The success of this project will be judged solely based on the efficiency and performance of the AI bot in playing Gomoku. Various algorithms can be implemented to optimize the bot's gameplay, and the technical constraints must be strictly adhered to throughout the development process.