#pragma once
#include <iostream>
#include <conio.h>
#include <Windows.h>

using namespace std;

enum KeyCode
{
    ArrowUp = 72,
    ArrowDown = 80,
    ArrowLeft = 75,
    ArrowRight = 77,
    Enter = 13,
    Space = 32,
    Esc = 27
};

class Console
{
    HANDLE descriptor;
    COORD coordinate;
    CONSOLE_SCREEN_BUFFER_INFO csbInfo;
public:
    Console()
    {
        descriptor = GetStdHandle(STD_OUTPUT_HANDLE);
    }
    void Clear()
    {
        system("cls");
    }

    void CursorGoTo(int row, int col)
    {
        coordinate.Y = row;
        coordinate.X = col;
        SetConsoleCursorPosition(descriptor, coordinate);
    }

    void PrintChar(int row, int col, char symbol)
    {
        CursorGoTo(row, col);
        cout << symbol;
    }
    void PrintString(int row, int col, string str)
    {
        CursorGoTo(row, col);
        cout << str;
    }

    void GetChar()
    {
        GetConsoleScreenBufferInfo(descriptor, &csbInfo);
    }
};
