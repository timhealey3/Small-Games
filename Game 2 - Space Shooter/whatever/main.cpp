#include <iostream>
#include "Game.h"
int main()
{
    std::srand(static_cast<unsigned>(time(NULL)));
    Game game;
    // GUI - start game?
    game.run();
    return 0;
}