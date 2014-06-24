#include "game.h"
#include <SDL/SDL.h>
int main (int argc, char* argv[]){
    Game game;
    game.runState(Game::States::MENU);
    return 0;
}
