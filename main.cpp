#include "game.h"
#include "utils.h"

#include <SDL/SDL.h>
int main (int argc, char* argv[]){
    try {
        printf("Working dir is: %s\n", getDirectory().c_str());
    } catch(int e){
        ;
    }
    Game game;
    game.runState(Game::States::MENU);
    return 0;

}
