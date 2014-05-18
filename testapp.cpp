#define FRAMERATE 60
#include <cstdlib>
#include "SDL/SDL.h"
#include "player.h"
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
Uint32 timeLeft(){
    static Uint32 nextTick = 0;
    Uint32 currentTick = SDL_GetTicks();

    if(nextTick <= currentTick){
        nextTick = currentTick + FRAMERATE;
        return 0;
    }
    else {
        return (nextTick-currentTick);
    }
}

SDL_Surface *screen = NULL;

int main (int argc, char *argv[]){

    if(SDL_Init(SDL_INIT_EVERYTHING) == -1){
        printf("Error");
    }

    screen = SDL_SetVideoMode(800, 600, 32, SDL_SWSURFACE);
    //SDL_WM_SetCaption("TESTAPP");

    Player player = Player(200, 300);
    player.init();
    Uint32 tickDelay = 0;
    bool loop = true;
    while(loop){
        while(SDL_PollEvent(&event)){
            if(event.type == SDL_QUIT){
                loop = false;
            }
            if(event.type == SDL_KEYDOWN){
                player.listen(event);
            }

        }
        tickDelay = timeLeft();
        SDL_Delay(tickDelay);
    }

    return 0;
}

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

    Player player = Player(200, 300);
    player.init();

    return 0;
}
*/
