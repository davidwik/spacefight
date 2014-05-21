#include "player.h"
#include "utils.h"
#include "animation.h"
void Player::init(){
    animName = "PLAY";
    animations[animName] = new Animation(2, true);
    animations[animName]->addFrame("gfx/1.jpg");
    animations[animName]->addFrame("gfx/2.jpg");
    animations[animName]->addFrame("gfx/3.jpg");

    animations["SHIP"] = new Animation(1, true);
    animations["SHIP"]->addFrame("gfx/player.png");
}

void Player::listen(SDL_Event event){
    Uint8 *keystates = SDL_GetKeyState(NULL);
    if(keystates[SDLK_RIGHT]){
        moveRight();
    }
    if(keystates[SDLK_LEFT]){
        moveLeft();
    }
    if(keystates[SDLK_DOWN]){
        animName = "PLAY";
        moveDown();
    }
    if(keystates[SDLK_UP]){
        animName = "SHIP";
        moveUp();
    }
    if(event.type == SDL_KEYDOWN){
        if(event.key.keysym.sym == SDLK_SPACE){
            animations[animName]->flipVertical();
        }
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
