#pragma once

#include <iostream>
#include <cstdlib>
#include <fstream>
#include <string>
#include <sstream>
#include <Windows.h>

// Implementation borrowed from https://github.com/MarioTalevski/game-of-life
// Will possibly do my own implementation, but I don't have a firm grasp over windows console manipulation

#define COLOR_RED SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED)
#define COLOR_GREEN SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN)
#define COLOR_BLUE SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_BLUE)
#define COLOR_RESET SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15)

const int gridSize = 25;

void printGrid(bool gridOne[gridSize + 1][gridSize + 1]);

void compareGrid(bool gridOne[gridSize+1][gridSize+1], bool gridTwo[gridSize+1][gridSize+1]);

void determineState(bool gridOne[gridSize + 1][gridSize + 1]);

void clearScreen();