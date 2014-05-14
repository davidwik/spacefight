#define TICK_INTERVAL 1000
#include <iostream>
#include <cstdlib>
#include "SDL/SDL.h"
#include "gameobject.h"
using namespace std;

SDL_Event event;
/**
 * This file is for trying out some c/c++ specifics
 *
 */
/*
Uint32 timeLeft(void){
    static Uint32 nextTick = 0;
    Uint32 currentTick = SDL_GetTicks();
    if(nextTick <= currentTick){
        nextTick = currentTick + TICK_INTERVAL;
        return 0;
    }
    else {
        return (nextTick-currentTick);
    }
}
*/



int main (int argc, char *argv[]){
/*
    Uint32 tickDelay = 0;
    bool loop = true;
    Uint32 randDelay = 0;
    while(loop){
        randDelay = rand() % 400;
        SDL_Delay(randDelay);
        printf("Delay: %d\n", randDelay);
        tickDelay = timeLeft();

        printf("%d\n", tickDelay);
        SDL_Delay(tickDelay);
    }
*/

    GameObject go;

    go.setXY(230,40);

    printf("Y is: %d", go.getY());
    printf("X is: %d", go.getPosition().x);
    return 0;
}
