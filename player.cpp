#include "player.h"
#include "utils.h"
#include "animation.h"

Player::Player(int x,
               int y,
               AnimationLibrary* a) : GameObject(x, y, a){
    position.x = x;
    position.y = y;
    animLib = a;
    objType = "player";
    printf("ObjectId: %d\n", id);
}


void Player::init(){
    printf("PPPP: %d\n\n", getWidth());
    if(!animLib->has("player-wait")){
        Animation* waitAnim = new Animation(4, true);
        waitAnim->addFrame("gfx/shipanim/ship-still01.png");
        waitAnim->addFrame("gfx/shipanim/ship-still02.png");
        animLib->add("player-wait", waitAnim);

    }
    if(!animLib->has("player-thrust")){
        Animation* thrustAnim = new Animation(6, true);
        thrustAnim->addFrame("gfx/shipanim/ship-thrust01.png");
        thrustAnim->addFrame("gfx/shipanim/ship-thrust02.png");
        thrustAnim->addFrame("gfx/shipanim/ship-thrust03.png");
        thrustAnim->addFrame("gfx/shipanim/ship-thrust04.png");
        animLib->add("player-thrust", thrustAnim);
    }
    animName = "player-wait";
}

void Player::listen(SDL_Event event){
    Uint8 *keystates = SDL_GetKeyState(NULL);
    if(keystates[SDLK_RIGHT]){
        animName = "player-thrust";
        moveRight();
    }
    if(keystates[SDLK_LEFT]){
        animName = "player-thrust";
        moveLeft();
    }
    if(keystates[SDLK_DOWN]){
        animName = "player-thrust";
        if(!keystates[SDLK_LCTRL]){
            moveDown();
        }

    }
    if(keystates[SDLK_UP]){
        animName = "player-thrust";
        if(!keystates[SDLK_LCTRL]){
            moveUp();
        }
    }
    if(!keystates[SDLK_UP] &&
       !keystates[SDLK_DOWN] &&
       !keystates[SDLK_LEFT] &&
       !keystates[SDLK_RIGHT]){
        animName = "player-wait";
    }

}

Player::~Player(){
    printf("Destroying the player instance - GameObjectId: %d\n", id);
}

void Player::update(){
    posUpdate();
}

void Player::draw(SDL_Surface *screen){
    applySurface(getX(), getY(), animLib->get(animName)->getFrame(), screen, NULL);
    drawBorder(screen);
}

void Player::handleCollision(vector <GameObject*> gameObjectList){

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
