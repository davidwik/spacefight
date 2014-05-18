#include "player.h"
#include "utils.h"
void Player::init(){
    image = loadImage("gfx/player.png");
}

void Player::listen(SDL_Event event){
    switch(event.key.keysym.sym){

    case SDLK_LEFT:
        moveLeft();
        break;
    case SDLK_RIGHT:
        moveRight();
    default:
        break;
   }
}

void Player::update(SDL_Surface *screen){
    applySurface(getX(), getY(), image, screen, NULL);
}

void Player::moveLeft(){
    position.x -=10;
}

void Player::moveRight(){
    position.x +=10;
}
