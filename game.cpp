#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include <cstdlib>
#include "utils.h"
#include "game.h"
#include "errorcodes.h"

#define FRAMERATE 60

void Game::run(){
    try {
        init();
        setBackground();
        gameLoop();
        waitForQuit(3000);
    } catch(int e){
        handleError(e);
    }
    SDL_Quit();
}

void Game::init(){
    if(SDL_Init(SDL_INIT_EVERYTHING) == -1){
        throw SDL_INIT_ERROR;
    }

    screen = SDL_SetVideoMode(SCREEN_WIDTH,
                              SCREEN_HEIGHT,
                              SCREEN_BPP,
                              SDL_SWSURFACE);
    if(screen == NULL){
        throw SDL_SCREEN_ERROR;
    }
    SDL_WM_SetCaption("Spaaace Fight!", NULL);
}

void Game::setBackground(){
    background = loadImage("gfx/background.jpg");
    applySurface(0, 0, background, screen, NULL);
}


void Game::waitForQuit(int ms){
    SDL_Delay(ms);
}

void Game::handleError(int e){
    switch(e){
    case SDL_INIT_ERROR:
        printf("Error intializing SDL!\n");
        exit(1);

    case SDL_SCREEN_ERROR:
        printf("Error setting screen mode\n");
        exit(1);

    case SDL_IMAGE_LOAD_ERROR:
        printf("Error loading image resource\n");
        exit(1);

    case UNKNOWN_ERROR:
        printf("Unknown error!\n");
        exit(1);
    }
}


void Game::gameLoop(){
    bool quit = false;

    while(quit == false){
        if(SDL_Flip(screen) == -1){
            throw(SDL_SCREEN_ERROR);
        }



        while(SDL_PollEvent(&event)){
            if(event.type == SDL_QUIT){
                printf("Quit received\n");
                quit = true;
            }
            if(event.key.keysym.sym == 27){
                printf("Escape press - qutting\n");
                quit = true;
            }
        }
        SDL_Delay(20);
    }

    SDL_Quit();
    exit(0);
}

Uint32 TimeLeft(){
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
