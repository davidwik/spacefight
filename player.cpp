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

    health = totalHealth;

}

void Player::listen(SDL_Event &event, vector <GameObject*> &refObjects){
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

    if(event.key.keysym.sym == SDLK_SPACE && event.type == SDL_KEYDOWN){
        fire(refObjects);
    }
}

void Player::fire(vector <GameObject*> &refObjects){
    int startX = static_cast<int>(rect.x + (rect.w/2));
    int startY = static_cast<int>(rect.y + (rect.h/2));

    Uint32 diff = SDL_GetTicks() - lastFired;
    Uint32 limit = 200;

    if(diff > limit){

        Fire* f = new Fire(Fire::Types::BULLET,
                           animLib,
                           startX,
                           startY,
                           id);
        f->init();
        refObjects.insert(refObjects.begin(),f);
        lastFired = SDL_GetTicks();
    }
}

Player::~Player(){
    printf("Destroying the player instance - GameObjectId: %d\n", id);
}

void Player::update(vector <GameObject*> &refObjects){
    posUpdate();
}


void Player::drawHP(SDL_Surface* screen){
    SDL_Rect healthBar;
    healthBar.w = 130;
    healthBar.h = 20;
    healthBar.x = 10;
    healthBar.y = screen->h - (healthBar.h+10);

    float percentHP = ((float) health / (float) totalHealth);
    int barLenght = static_cast<int>(percentHP*healthBar.w);
    SDL_Rect barBorder = healthBar;

    healthBar.w = barLenght;

    SDL_FillRect(
        screen,
        &healthBar,
        SDL_MapRGB(
            screen->format, 0, 170, 0
        )
    );
    drawRect(screen, barBorder, SDL_MapRGB(screen->format, 0, 255, 0));
}

void Player::draw(SDL_Surface *screen){
    applySurface(getX(), getY(), animLib->get(animName)->getFrame(), screen, NULL);
    drawBorder(screen);
    drawHP(screen);
}

void Player::handleCollision(vector <GameObject*> gameObjectList){
    for(auto it = gameObjectList.begin();
        it != gameObjectList.end();
        it++){

        // Is it fire?!
        if((*it)->objectType() == "fire" && (*it)->getParentId() != 0){
            loseHealth(static_cast<Fire*>(*it)->getDamage());
            (*it)->terminate();
            if(health <= 0){
                health = totalHealth;
            }
        }



    }
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
