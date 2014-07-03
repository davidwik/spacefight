#include "player.h"
#include "utils.h"
#include "animation.h"
#define MOVESPEED 7
#define AMMO_SPECIAL_DURATION 30000

Player::Player(int x,
               int y,
               AnimationLibrary* a,
               SoundLibrary* snd) : GameObject(x, y, a, snd){
    position.x = x;
    position.y = y;
    zIndex = 5;
    animLib = a;
    soundLib = snd;
    objType = "player";
    printf("ObjectId: %d\n", id);
    shieldHealth = 0;
    shieldHealthTotal = 180;
    totalHealth = 100;
    health = totalHealth;
    shieldCoolDown = 0;

    lives = 5;
    ammoType = (int) Player::AmmoTypes::SINGLE;
    specialAmmoUntil = 0;

    lastFired = 0;
    fired = false;
    shieldActive = false;

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

    if(soundLib != NULL){
        if(!soundLib->has("shields-active")){
            soundLib->add("shields-active",
                          new Sound(
                              "res/audio/shields-on.ogg",
                              Sound::Types::EFFECT,
                              4)
            );
        }
    }
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

    if(keystates[SDLK_LCTRL] || keystates[SDLK_RCTRL]){
        shieldOn();
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
        if(!shieldActive){
            fire(refObjects);
        }
    }
}

void Player::fire(vector <GameObject*> &refObjects){
    int startX = static_cast<int>(rect.x + (rect.w/2));
    int startY = static_cast<int>(rect.y + (rect.h/2));

    Uint32 diff = SDL_GetTicks() - lastFired;
    Uint32 limit = 200;

    if(diff > limit){

        if(ammoType == (int) Player::AmmoTypes::SINGLE){
            Fire* f = new Fire(Fire::Types::PLAYER_BULLET,
                               animLib,
                               soundLib,
                               startX,
                               startY,
                               id);

            f->init();

            refObjects.insert(refObjects.begin(),f);
        }
        else if(ammoType == (int) Player::AmmoTypes::TRIPLE){
            Fire* a = new Fire(Fire::Types::PLAYER_BULLET,
                               animLib,
                               soundLib,
                               startX,
                               startY,
                               id);

            Fire* b = new Fire(Fire::Types::PLAYER_BULLET,
                               animLib,
                               soundLib,
                               startX,
                               startY,
                               id);
            Fire* c = new Fire(Fire::Types::PLAYER_BULLET,
                               animLib,
                               soundLib,
                               startX,
                               startY,
                               id);
            a->setDX(-2);
            b->setDX(2);
            a->init();
            b->init();
            c->init();
            refObjects.insert(refObjects.begin(), a);
            refObjects.insert(refObjects.begin(), b);
            refObjects.insert(refObjects.begin(), c);
        }


        lastFired = SDL_GetTicks();
    }
}

Player::~Player(){
    printf("Destroying the player instance - GameObjectId: %d\n", id);
}

void Player::update(vector <GameObject*> &refObjects){
    posUpdate();

    if(specialAmmoUntil < SDL_GetTicks()){
        ammoType = (int) Player::AmmoTypes::SINGLE;
    }

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

    if(!shieldActive && shieldCoolDown < SDL_GetTicks()){
        int ch = soundLib->getReservedChannel("shield-noise");
        if(ch != -1){
            soundLib->stopReservedChannel("shield-noise");
        }
        if(shieldHealth < shieldHealthTotal){
            shieldHealth += 2;
        }
    }

}

void Player::drawHeartBar(SDL_Surface* surface){
    Animation* an = animLib->get("heart-anim");
    for(int i = 0; i < lives; i++){
        applySurface(10+(23*i),
                     surface->h-64,
                     an->getFrame(),
                     surface,
                     NULL);
    }

}

void Player::drawShield(SDL_Surface* surface){
    SDL_Surface* frame = animLib->get("player-shield")->getFrame();
    applySurface(
        getX()-33,
        getY()-24,
        animLib->get("player-shield")->getFrame(),
        surface,
            NULL
    );
    SDL_Rect r;
    r.x = rect.x-33;
    r.y = rect.y-24;
    r.w = frame->w;
    r.h = frame->h;
    rect = r;

}

void Player::drawHP(SDL_Surface* screen){
    SDL_Rect healthBar;
    healthBar.w = 130;
    healthBar.h = 20;
    healthBar.x = 10;
    healthBar.y = screen->h - (healthBar.h+20);

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

void Player::drawShieldBar(SDL_Surface* screen){
    SDL_Rect shieldBar;
    int sLenght = shieldHealthTotal-50;
    shieldBar.w = sLenght;
    shieldBar.h = 4;
    shieldBar.x = 10;
    shieldBar.y = screen->h - (shieldBar.h+10);

    float percentShield = ((float) shieldHealth / (float) shieldHealthTotal);
    int length = static_cast<int>(percentShield*sLenght);

    SDL_Rect shieldBarBorder = shieldBar;
    shieldBarBorder.w = sLenght;
    shieldBar.w = length;
    SDL_FillRect(
        screen,
        &shieldBar,
        SDL_MapRGB(
            screen->format, 101, 199, 224
        )
    );
    drawRect(screen, shieldBarBorder, SDL_MapRGB(screen->format, 64, 110, 121));
}

void Player::shieldOn(){
    if(shieldHealth > 0 && SDL_GetTicks() > shieldCoolDown){
        shieldHealth -= 2;
        shieldActive = true;

        if(soundLib->getReservedChannel("shield-noise") == -1){
            int ch = soundLib->get("shields-active")->playLoopedEffect();
            soundLib->addReservedChannel("shield-noise", ch);
        }
    }
    else {
        int ch = soundLib->getReservedChannel("shield-noise");
        if(ch != -1){
            soundLib->stopReservedChannel("shield-noise");
        }
        if(shieldCoolDown <= SDL_GetTicks()){
            shieldCoolDown = SDL_GetTicks() + 1000;
        }
        shieldActive = false;
    }
}

void Player::draw(SDL_Surface *screen){
    applySurface(getX(), getY(), animLib->get(animName)->getFrame(), screen, NULL);
    if(shieldActive){
        drawShield(screen);
    }
    drawBorder(screen);
    drawHP(screen);
    drawHeartBar(screen);
    drawShieldBar(screen);
}

void Player::handleCollision(vector <GameObject*> gameObjectList, vector <GameObject*> &refObjects){
    for(auto it = gameObjectList.begin();
        it != gameObjectList.end();
        it++){

        // Is it fire?!
        if((*it)->objectType() == "fire" && static_cast<Fire*>(*it)->getType() == Fire::Types::ENEMY_BULLET){
            if(!shieldActive){
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
                            soundLib,
                            getX() + (int) (r.w/2),
                            getY() + (int) (r.h/2)
                        );
                        refObjects.push_back(ex);
                        terminate();
                    }
                }
            }
            if(shieldHealth > 25){
                shieldHealth -= 20;
            }

        }

        if((*it)->objectType() == "bonus"){
            soundLib->play("bonus", 0);
            Bonus* b = static_cast<Bonus*>(*it);

            switch(b->getType()){

            case Bonus::Types::HEART:
                lives++;
                break;

            case Bonus::Types::SHIELD:
                shieldHealthTotal += 50;
                break;

            case Bonus::Types::AMMO:
                ammoType = (int) Player::AmmoTypes::TRIPLE;
                specialAmmoUntil = SDL_GetTicks() + AMMO_SPECIAL_DURATION;
                break;

            default:
                break;
            }

            (*it)->terminate();
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
