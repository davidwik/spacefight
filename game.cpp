#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include <cstdlib>
#include "utils.h"
#include "game.h"
#include "errorcodes.h"
#include <typeinfo>
#include <iostream>
#include <string>
#define FRAMERATE 60

void Game::run(){
    try {
        init();
        setBackground();
        gameLoop();
    } catch(int e){
        handleError(e);
    }

}

Game::~Game(){
    printf("Running Game deconstructor!\n");
    for(vector <GameObject*>::iterator it = gameObjectList.begin();
        it != gameObjectList.end();
        it++){
        if((*it)->objectType() == "player"){
            delete static_cast<Player*>(*it);
        }
        else if((*it)->objectType() == "enemy"){
            delete static_cast<Enemy*>(*it);
        }

    }
    delete animLib;

    SDL_FreeSurface(background);
    SDL_FreeSurface(screen); // Should maybe be removed?
    gameObjectList.clear();
    if(player == NULL){
        printf("Player is surely dead!");
    }
    printf("Qutting SDL\n");
    SDL_Quit();
    printf("Returning to main!\n");
}


void Game::init(){
    if(SDL_Init(SDL_INIT_EVERYTHING) == -1){
        throw SDL_INIT_ERROR;
    }

    screen = SDL_SetVideoMode(SCREEN_WIDTH,
                              SCREEN_HEIGHT,
                              SCREEN_BPP,
                              SDL_HWSURFACE);
    if(screen == NULL){
        throw SDL_SCREEN_ERROR;
    }

    animLib = new AnimationLibrary();
    player = new Player(200, 300, animLib);
    gameObjectList.push_back(new Enemy(Enemy::Types::DRUNK, animLib, 100, 40));
    gameObjectList.push_back(new Enemy(Enemy::Types::EATER, animLib, 200, 40));
    gameObjectList.push_back(player);
    for(vector <GameObject*>::iterator it = gameObjectList.begin();
        it != gameObjectList.end();
        it++){
        (*it)->init();
    }
    SDL_WM_SetCaption("Spaaace Fight!", NULL);
}

void Game::setBackground(){
    background = loadImage("gfx/background.jpg");
    applySurface(0, 0, background, screen, NULL);
}

void Game::handleError(int e){
    switch(e){
    case SDL_INIT_ERROR:
        printf("Error intializing SDL!\n");
        break;

    case SDL_SCREEN_ERROR:
        printf("Error setting screen mode\n");
        break;

    case SDL_IMAGE_LOAD_ERROR:
        printf("Error loading image resource\n");
        break;

    case UNKNOWN_ERROR:
        printf("Unknown error!\n");
        break;
    }
}

void Game::gameLoop(){
    bool quit = false;
    player->setX(30);
    player->setY(40);
    while(quit == false){

        applySurface(0, 0, background, screen, NULL);
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
        for(vector <GameObject*>::iterator it = gameObjectList.begin();
            it != gameObjectList.end();
            it++){
            (*it)->listen(event);
            (*it)->update(screen);
        }

        SDL_Delay(20);
        if(SDL_Flip(screen) == -1){
            throw(SDL_SCREEN_ERROR);
        }
        //SDL_UpdateRect(screen, 0, 0, 0, 0);

    }
    printf("Out of gameloop!\n");
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
