#pragma once
#include <vector>
#include "Console.h"

using namespace std;

struct CellStruct
{
    int row;
    int col;
};

vector<CellStruct> Diff{ {-1, 0}, {-1, 1}, {0, 1}, {1, 1}, {1, 0}, {1, -1}, {0, -1}, {-1, -1} };

enum CellState
{
    Empty,
    Living,
    Born,
    Dying
};

class Cell
{
    int row;
    int col;
    CellState state;
    int neighbors;
public:
    Cell(int row = 0, int col = 0, CellState state = CellState::Empty)
        : row{ row }, col{ col },
        state{ state },
        neighbors{ 0 } {};
    int& Row() { return this->row; }
    int& Col() { return this->col; }
    CellState& State() { return this->state; }
    int& Neighbors() { return this->neighbors; }

    void Print(Console console)
    {
        console.PrintString(row, col * 2, string(2, (char)178));
    }
};
