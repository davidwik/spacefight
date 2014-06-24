#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include <cstdlib>
#include "utils.h"
#include "game.h"
#include "fire.h"
#include "errorcodes.h"
#include "constants.h"
#include "collision.h"
#include <typeinfo>
#include <iostream>
#include <string>
#include <algorithm>

#include "explosion.h"

void Game::run(){
    try {
        init();
        setBackground();
        gameLoop();
    } catch(int e){
        handleError(e);
    }

}

void Game::deleteObject(GameObject* go){
    if(go->objectType() == "player"){
        delete static_cast<Player*>(go);
    }
    else if(go->objectType() == "enemy"){
        delete static_cast<Enemy*>(go);
    }
    else if(go->objectType() == "fire"){
        delete static_cast<Fire*>(go);
    }
    else if(go->objectType() == "explosion"){
        delete static_cast<Explosion*>(go);
    }
    else {
        printf("WHAT?!");
    }
    go = NULL;
}

Game::~Game(){
    printf("Running Game deconstructor!\n");
    for(vector <GameObject*>::iterator it = gameObjectList.begin();
        it != gameObjectList.end();
        it++){
        deleteObject((*it));
        (*it) = NULL;
    }
    gameObjectList.empty();
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
                              SDL_HWSURFACE | SDL_DOUBLEBUF);
    if(screen == NULL){
        throw SDL_SCREEN_ERROR;
    }
    gameObjectList.reserve(1000);
    animLib = new AnimationLibrary();
    player = new Player(200, 300, animLib);
    gameObjectList.push_back(new Enemy(Enemy::Types::DRUNK, animLib, 100, 40));
    gameObjectList.push_back(new Enemy(Enemy::Types::EATER, animLib, 200, 40));
    gameObjectList.push_back(new Enemy(Enemy::Types::DRUNK, animLib, 100, 40));
    gameObjectList.push_back(new Enemy(Enemy::Types::EATER, animLib, 200, 40));
    gameObjectList.push_back(new Enemy(Enemy::Types::DRUNK, animLib, 100, 40));
    gameObjectList.push_back(new Enemy(Enemy::Types::EATER, animLib, 200, 40));
    gameObjectList.push_back(player);

    for(vector <GameObject*>::iterator it = gameObjectList.begin();
        it != gameObjectList.end();
        it++){
        (*it)->init();
    }
    sort(gameObjectList.begin(), gameObjectList.end());

    SDL_WM_SetCaption("Spaaace Fight!", NULL);
}

void Game::setBackground(){
    background = loadImage("gfx/background2.jpg");
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

        vector <GameObject*>::iterator it;
        // Check update and draw!
        for(vector <GameObject*>::iterator it = gameObjectList.begin();
            it != gameObjectList.end();
            it++){
            (*it)->listen(event, gameObjectList);
            (*it)->update(gameObjectList);
            (*it)->draw(screen);
        }


        // Run the collision check
        Collision::runCollisionCheck(gameObjectList);

        // Remove dying objects.
        int numDying = 0;
        for(auto it = gameObjectList.begin();
            it != gameObjectList.end();
            it++){
            if((*it)->killMe()){
                numDying++;
            }
        }
        // Clean up vector of dying objects
        while(numDying > 0){
            for(vector <GameObject*>::iterator iter = gameObjectList.begin();
                iter != gameObjectList.end();
                iter++){
                if((*iter)->killMe()){
                    deleteObject((*iter));
                    (*iter) = NULL;
                    iter = gameObjectList.erase(iter);
                    numDying--;
                    break;
                }
            }
        }
        sort(gameObjectList.begin(), gameObjectList.end());

        SDL_Delay(static_cast<int>(1000/FRAMERATE));
        if(SDL_Flip(screen) == -1){
            throw(SDL_SCREEN_ERROR);
        }
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
