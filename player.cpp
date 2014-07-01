#include "player.h"
#include "utils.h"
#include "animation.h"
#define MOVESPEED 7

Player::Player(int x,
               int y,
               AnimationLibrary* a) : GameObject(x, y, a){
    position.x = x;
    position.y = y;
    zIndex = 0;
    animLib = a;
    objType = "player";
    printf("ObjectId: %d\n", id);
}


void Player::init(){
    if(!animLib->has("player-wait")){
        Animation* waitAnim = new Animation(4, true);
        waitAnim->addFrame("res/gfx/sprites/ship-still01.png");
        waitAnim->addFrame("res/gfx/sprites/ship-still02.png");
        animLib->add("player-wait", waitAnim);

    }
    if(!animLib->has("player-thrust")){
        Animation* thrustAnim = new Animation(6, true);
        thrustAnim->addFrame("res/gfx/sprites/ship-thrust01.png");
        thrustAnim->addFrame("res/gfx/sprites/ship-thrust02.png");
        thrustAnim->addFrame("res/gfx/sprites/ship-thrust03.png");
        thrustAnim->addFrame("res/gfx/sprites/ship-thrust04.png");
        animLib->add("player-thrust", thrustAnim);
    }

    if(!animLib->has("player-shield")){
        Animation* shield = new Animation(50, true);
        shield->addFrame("res/gfx/sprites/shield01.png");
        shield->addFrame("res/gfx/sprites/shield02.png");
        shield->addFrame("res/gfx/sprites/shield03.png");
        shield->addFrame("res/gfx/sprites/shield04.png");
        shield->addFrame("res/gfx/sprites/shield01.png");
        shield->addFrame("res/gfx/sprites/shield02.png");
        shield->addFrame("res/gfx/sprites/shield03.png");
        shield->addFrame("res/gfx/sprites/shield04.png");
        shield->addFrame("res/gfx/sprites/shield05.png");
        shield->addFrame("res/gfx/sprites/shield06.png");

        animLib->add("player-shield", shield);
    }

    if(!animLib->has("heart-anim")){
        Animation* heartAnim = new Animation(10, true);
        heartAnim->addFrame("res/gfx/sprites/heart01.png");
        heartAnim->addFrame("res/gfx/sprites/heart02.png");
        heartAnim->addFrame("res/gfx/sprites/heart03.png");
        heartAnim->addFrame("res/gfx/sprites/heart04.png");
        heartAnim->addFrame("res/gfx/sprites/heart05.png");
        animLib->add("heart-anim", heartAnim);
    }

    if(!animLib->has("game-over")){
        Animation* gameOver = new Animation(1, true);
        gameOver->addFrame("res/gfx/static/gameover.png");
        animLib->add("game-over", gameOver);
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
        moveDown();
    }
    if(keystates[SDLK_UP]){
        animName = "player-thrust";
        moveUp();
    }

    if(keystates[SDLK_LCTRL]){
        shieldActive = true;
    }
    else {
        shieldActive = false;
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

        Fire* f = new Fire(Fire::Types::PLAYER_BULLET,
                           animLib,
                           startX,
                           startY,
                           id);

        if(soundLib != NULL){
            f->setSoundLibrary(soundLib);
        }
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

    // Make sure the player doesn't leave..
    if(getX() + rect.w > SCREEN_WIDTH){
        setX(SCREEN_WIDTH-rect.w);
    }
    if(getX() < 0){
        setX(0);
    }
    if(getY() < -10){
        setY(-10);
    }
    if(getY() + (int) (rect.h/2) > SCREEN_HEIGHT){
        setY(SCREEN_HEIGHT -(int) (rect.h/2));
    }

}

void Player::drawHeartBar(SDL_Surface* surface){
    Animation* an = animLib->get("heart-anim");
    for(int i = 0; i < lives; i++){
        applySurface(10+(23*i),
                     surface->h-60,
                     an->getFrame(),
                     surface,
                     NULL);
    }

}

void Player::drawShield(SDL_Surface* surface){
    applySurface(
        rect.x-33,
        rect.y-24,
        animLib->get("player-shield")->getFrame(),
        surface,
            NULL
    );
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
    if(shieldActive){
        drawShield(screen);
    }
    drawBorder(screen);
    drawHP(screen);
    drawHeartBar(screen);


}

void Player::handleCollision(vector <GameObject*> gameObjectList, vector <GameObject*> &refObjects){
    for(auto it = gameObjectList.begin();
        it != gameObjectList.end();
        it++){

        // Is it fire?!
        if((*it)->objectType() == "fire" && static_cast<Fire*>(*it)->getType() == Fire::Types::ENEMY_BULLET){

            loseHealth(static_cast<Fire*>(*it)->getDamage());
            if(health <= 0){
                if(lives > 1){
                    lives--;
                    health = totalHealth;
                }
                else {
                    SDL_Rect r = getRect();
                    Explosion* ex = new Explosion(
                        Explosion::Types::BIG,
                        animLib,
                        getX() + (int) (r.w/2),
                        getY() + (int) (r.h/2)
                    );
                    refObjects.push_back(ex);
                    terminate();
                }
            }
        }
    }
}


void Player::moveLeft(){
    setX(getX()-MOVESPEED);
}

void Player::moveRight(){
    setX(getX()+MOVESPEED);
}

void Player::moveUp(){
    setY(getY()-MOVESPEED);
}

void Player::moveDown(){
    setY(getY()+MOVESPEED);
}
