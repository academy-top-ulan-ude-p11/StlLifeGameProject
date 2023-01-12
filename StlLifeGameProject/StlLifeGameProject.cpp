#include <iostream>
#include <Windows.h>
#include <vector>
#include <algorithm>

using namespace std;

class Console
{
    HANDLE descriptor;
    COORD coordinate;
public:
    Console()
    {
        descriptor = GetStdHandle(STD_OUTPUT_HANDLE);
    }
    void Clear()
    {
        system("cls");
    }
    void PrintChar(int row, int col, char symbol)
    {
        coordinate.Y = row;
        coordinate.X = col;
        SetConsoleCursorPosition(descriptor, coordinate);
        cout << symbol;
    }
};

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
    Cell(int row, int col, CellState state = CellState::Empty)
        : row{ row }, col{ col },
        state{ state },
        neighbors{ 0 } {};
    int& Row() { return this->row; }
    int& Col() { return this->col; }
    CellState& State() { return this->state; }
    int& Neighbors() { return this->neighbors; }

    void Print(Console console)
    {
        console.PrintChar(row, col, (char)178);
    }
};


class Game
{
    Console console;
    vector<Cell> colony;
public:
    Game()
    {

    }
    void SetColony()
    {
        do {
            char answer;
            cout << "input cell? <y/n>";
            cin >> answer;
            if (tolower(answer) == 'n')
                break;
            
            int row, col;
            cout << "input row: ";
            cin >> row;
            cout << "input col: ";
            cin >> col;
            colony.push_back(Cell(row, col, CellState::Living));
        } while (true);
    }

    void PrintColony()
    {
        console.Clear();
        for (auto cell : colony)
        {
            cell.Print(console);
        }
    }
    
    vector<Cell>::iterator isColonyCell(Cell cell)
    {
        return find_if(colony.begin(), colony.end(), [&cell](auto item) {
            return cell.Row() == item.Row() && cell.Col() == item.Col();
            });
    }

    void Step()
    {
        for (auto cell : colony)
            cell.Neighbors() = 0;

        for (auto cell : colony)
        {
            if (cell.State() == CellState::Born)
                continue;
            for (auto diff : Diff)
            {
                int row = cell.Row() + diff.row;
                int col = cell.Col() + diff.col;
                if (row < 0 || col < 0)
                    continue;

                Cell cellTemp(row, col);
                cellTemp.State() = CellState::Born;
                
                auto cellFind = isColonyCell(cellTemp);

                if (cellFind == colony.end())
                {
                    cellTemp.Neighbors()++;
                    colony.push_back(cellTemp);
                }
                else
                    cellFind->Neighbors()++;
            }
        }
        for (auto cell = colony.begin(); cell != colony.end(); cell++)
        {
            if (cell->State() == CellState::Living)
            {
                if (cell->Neighbors() < 2 || cell->Neighbors() > 3)
                    colony.erase(cell);
            }
            else
            {
                if (cell->Neighbors() != 3)
                    colony.erase(cell);
                else
                    cell->State() = CellState::Living;
            }
        }
    }
};

int main()
{
    Game game;
    game.SetColony();
    game.PrintColony();
    game.Step();
    game.PrintColony();
}
