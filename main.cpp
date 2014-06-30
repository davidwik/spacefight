#include <iostream>
#include <SDL/SDL.h>
#include "constants.h"
#include "game.h"
#include "utils.h"

int main (int argc, char* argv[]){
    try {
        printf("Working dir is: %s\n", getDirectory().c_str());
    } catch(int e){
        ;
    }

    Game g;
    g.runState(Game::States::MENU);

    return 0;
}
