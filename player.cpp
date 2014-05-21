#include "player.h"
#include "utils.h"
#include "animation.h"
void Player::init(){
    animName = "WAIT";
    animations[animName] = new Animation(4, true);
    animations[animName]->addFrame("gfx/shipanim/ship-still01.png");
    animations[animName]->addFrame("gfx/shipanim/ship-still02.png");


    animations["THRUST"] = new Animation(6, true);
    animations["THRUST"]->addFrame("gfx/shipanim/ship-thrust01.png");
    animations["THRUST"]->addFrame("gfx/shipanim/ship-thrust02.png");
    animations["THRUST"]->addFrame("gfx/shipanim/ship-thrust03.png");
    animations["THRUST"]->addFrame("gfx/shipanim/ship-thrust04.png");
}

void Player::listen(SDL_Event event){
    Uint8 *keystates = SDL_GetKeyState(NULL);
    if(keystates[SDLK_RIGHT]){
        animName = "THRUST";
        moveRight();
    }
    if(keystates[SDLK_LEFT]){
        animName = "THRUST";
        moveLeft();
    }
    if(keystates[SDLK_DOWN]){
        animName = "THRUST";
        if(!keystates[SDLK_LCTRL]){
            moveDown();
        }

    }
    if(keystates[SDLK_UP]){
        animName = "THRUST";
        if(!keystates[SDLK_LCTRL]){
            moveUp();
        }
    }
    if(!keystates[SDLK_UP] &&
       !keystates[SDLK_DOWN] &&
       !keystates[SDLK_LEFT] &&
       !keystates[SDLK_RIGHT]){
        animName = "WAIT";
        }


}

Player::~Player(){
    printf("Killing player..\n");
}

void Player::update(SDL_Surface *screen){
    applySurface(getX(), getY(), animations[animName]->getFrame(), screen, NULL);
}

void Player::moveLeft(){
    setX(getX()-10);
}

void Player::moveRight(){
    setX(getX()+10);
}

void Player::moveUp(){
    setY(getY()-10);
}

void Player::moveDown(){
    setY(getY()+10);
}
