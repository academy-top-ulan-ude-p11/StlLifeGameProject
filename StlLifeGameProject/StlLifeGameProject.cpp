#include <vector>
#include <algorithm>
#include <thread>
#include "Game.h"

using namespace std;

int main()
{
    Game game;
    game.SetColony();

    KeyCode key;
    while (1)
    {
        if (_kbhit())
        {
            key = (KeyCode)_getch();
            if (key == KeyCode::Esc)
                break;
        }
        game.PrintColony();
        game.Step();
        this_thread::sleep_for(1000ms);
    }
}
