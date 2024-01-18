#include <iostream>
#include "Game.h"
int main()
{
    // init rand
    std::srand(static_cast<unsigned>(time(NULL)));
    // window managment 
    Game game;
    // Game loop
    while (game.getWindowIsOpen() && !game.getEndGame()) {
        // while getting events
        game.update();
        game.render();
    }

    return 0;
}