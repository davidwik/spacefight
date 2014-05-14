#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include <cstdlib>
#include "utils.h"
#include "game.h"
#include "errorcodes.h"

void Game::run(){
    try {
        init();
        setBackground();
        gameLoop();
        waitForQuit(3000);
    } catch(int e){
        handleError(e);
    }
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
    if(SDL_Flip(screen) == -1){
        throw(SDL_SCREEN_ERROR);
    }
}
