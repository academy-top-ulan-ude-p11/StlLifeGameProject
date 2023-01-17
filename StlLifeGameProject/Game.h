#pragma once
#include "Console.h"
#include "Cell.h"

using namespace std;

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
        KeyCode key;
        int row{};
        int col{};
        console.CursorGoTo(row, col * 2);
        bool isStart{ false };
        while (1)
        {
            key = (KeyCode)_getch();
            Cell cell;
            vector<Cell>::iterator it;
            
            switch (key)
            {
            case ArrowUp:
                if (row > 0)
                    row--;
                break;
            case ArrowDown:
                if (row < 50)
                    row++;
                break;
            case ArrowLeft:
                if (col > 0)
                    col--;
                break;
            case ArrowRight:
                if (col < 80)
                    col++;
                break;
            case Enter:
                isStart = true;
                break;
            case Space:
                cell = Cell(row, col);
                it = isColonyCell(cell);
                if (it == colony.end())
                    colony.push_back(Cell(row, col));
                else
                    colony.erase(it);
                PrintColony();
                break;
            case Esc:
                exit(1);
                break;
            default:
                break;
            }

            
            console.CursorGoTo(row, col * 2);
            if (isStart)
                break;
        }

        /*
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
        */
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
        for (auto cell = colony.begin(); cell != colony.end(); cell++)
        {
            cell->Neighbors() = 0;
            for (auto diff : Diff)
            {
                int row = cell->Row() + diff.row;
                int col = cell->Col() + diff.col;
                if (isColonyCell(Cell{ row, col }) != colony.end())
                    cell->Neighbors() += 1;
            }
            if (cell->Neighbors() < 2 || cell->Neighbors() > 3)
                cell->State() = CellState::Dying;
        }

        int index{};
        while (index < colony.size())
        {
            for (auto diff : Diff)
            {
                Cell cellTemp = Cell(colony[index].Row() + diff.row, colony[index].Col() + diff.col);
                if (isColonyCell(cellTemp) == colony.end())
                {
                    for (auto subdiff : Diff)
                    {
                        int row = cellTemp.Row() + subdiff.row;
                        int col = cellTemp.Col() + subdiff.col;
                        auto cellFind = isColonyCell(Cell{ row, col });
                        if (cellFind != colony.end() && cellFind->State() != CellState::Born)
                            cellTemp.Neighbors()++;
                    }
                    if (cellTemp.Neighbors() == 3)
                    {
                        cellTemp.State() = CellState::Born;
                        colony.push_back(cellTemp);
                    }
                }
            }
            index++;
        }

        index = 0;
        while (index < colony.size())
        {
            if (colony[index].State() == CellState::Dying)
                colony.erase(colony.begin() + index);
            else
                colony[index++].State() = CellState::Living;
        }


    }
};