#include <iostream>
#include <SDL/SDL.h>
#include <physfs.h>
#include "constants.h"
#include "game.h"
#include "utils.h"
#include "physfsrwops.h"

int main (int argc, char* argv[]){
    try {
        printf("Working dir is: %s\n", getDirectory().c_str());
    } catch(int e){
        ;
    }

    PHYSFS_init(NULL);
    PHYSFS_addToSearchPath(ARCHIVE,1);
    Game g;
    g.runState(Game::States::MENU);

    return 0;
}
