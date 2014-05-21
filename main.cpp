#include "game.h"
#include <SDL/SDL.h>
int main (int argc, char* argv[]){
    Game game;
    game.run();
    SDL_Quit();
    printf("SDL_Quit\n");
    return 0;
}
