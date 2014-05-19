#include "player.h"
#include "utils.h"
void Player::init(){
    image = loadImage("gfx/player.png", true);
    if(image == NULL){
        printf("GAIL !");
    }
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
        moveDown();
    }
    if(keystates[SDLK_UP]){
        moveUp();
    }

}

Player::~Player(){
    SDL_FreeSurface(image);
    printf("Killing player..\n");
}

void Player::update(SDL_Surface *screen){
    applySurface(getX(), getY(), image, screen, NULL);
    //SDL_Flip(screen);
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
