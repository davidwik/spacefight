#include <iostream>
#include "constants.h"
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "utils.h"
#include <physfs.h>
#include "physfsrwops.h"

using namespace std;

int main(int argc, char* argv[]){
    SDL_Init(SDL_INIT_EVERYTHING);

    SDL_Surface* screen = NULL;
    SDL_Surface* img = NULL;
    SDL_RWops *rw = NULL;

    screen = SDL_SetVideoMode(800, 600, 32, SDL_SWSURFACE);
    PHYSFS_init(NULL);
    PHYSFS_addToSearchPath("mass.dat", 1);

    if ((rw=PHYSFSRWOPS_openRead("res/gfx/static/background.jpg\0")) == NULL){
        printf("NO FILe!!: %s\n", PHYSFS_getLastError());
        return 1; //false; //file doesn't exist
    }
    img = IMG_Load_RW(rw,0);

    SDL_FreeRW(rw);

    applySurface(0, 0, img, screen);
    SDL_Flip(screen);
    SDL_Delay(3000);

    SDL_Quit();


    return 0;
}
