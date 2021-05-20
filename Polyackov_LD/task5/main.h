#pragma once

#include <iostream>
#include <iomanip> //Äëÿ setw
#include <Windows.h>
#include <fstream>
#include <ctime>
#include <limits>
#include <string>
#include <vector>
#include <conio.h>

#pragma warning(disable:4996)

using namespace std;

enum ConsoleColor {
    BLACK = 0,
    BLUE = 1,
    GREEN = 2,
    CYAN = 3,
    RED = 4,
    MAGENTA = 5,
    BROWN = 6,
    LIGHTGRAY = 7,
    DARKGRAY = 8,
    LIGHTBLUE = 9,
    LIGHTGREEN = 10,
    LIGHTCYAN = 11,
    LIGHTRED = 12,
    LIGHTMAGENTA = 13,
    YELLOW = 14,
    WHITE = 15
};

enum KeyCodes
{
    BACKSPACE = 8,
    ENTER = 13
};
