#include "enemy.h"
#include "utils.h"
#include <string>
#include <cstdlib>
#include <cmath>
using namespace std;

Enemy::Enemy(Enemy::Types type,
      AnimationLibrary* a,
      int x,
      int y): GameObject(x, y, a){
        position.x = x;
        position.y = y;
        animLib = a;
        objType = "enemy";
        t = (int) type;
        dx = (rand()%20)+3;
        dy = 0;
        zIndex = 0;
        printf("EnemyType: %d\n", t);
        printf("ObjectId: %d\n", id);

}

void Enemy::listen(SDL_Event &event, vector <GameObject*> &refObjects){
    ;
}

void Enemy::update(vector <GameObject*> &refObjects){
    if(position.x > SCREEN_WIDTH){
        dx = ~dx+1;
        position.x = SCREEN_WIDTH-1;
    }
    else if(position.x < 0){
        position.x = 1;
        dx = ~dx+1;
    }

    if(dy == 0){
        dy = doubleToInt(cos((double) position.x*300));
    }

    if(position.x == 400 || position.y == 200){
        dy = ~dy+1;
        dx = ~dx+1;
    }

    if(position.y > (int) SCREEN_HEIGHT/2){
        dy = ~dy+1;
    }
    if(position.y < 0){
        dy = ~dy+1;
    }
    position.x += dx;
    position.y += dy;
    posUpdate();

    int t = rand()%100;
    if(t < triggerHappiness){
        fire(refObjects);
    }
}

void Enemy::handleCollision(vector <GameObject*> gameObjectList, vector <GameObject*> &refObjects){

    for(vector <GameObject*>::iterator it = gameObjectList.begin();
        it != gameObjectList.end();
        it++){

        // Check if it's a fire
        if((*it)->objectType() == "fire" && (*it)->getParentId() == 0){
            loseHealth(static_cast<Fire*>(*it)->getDamage());

            if(health <= 0){
                terminate();
            }

        }
    }
}

void Enemy::drawHealthBar(SDL_Surface* surface){
    SDL_Rect healthBar;

    healthBar.w = 80;
    healthBar.h = 5;
    healthBar.x = getX()+(rect.w/2)-(healthBar.w/2);
    healthBar.y = getY()-10;
    SDL_Rect healthBorder = healthBar;
    float percentHP = ((float) health / (float) totalHealth);
    int barLenght = static_cast<int>((percentHP*80));
    healthBar.w = barLenght;

    SDL_FillRect(
        surface,
        &healthBar,
        SDL_MapRGB(
            surface->format, 180, 0, 0
        )
    );
    drawRect(surface, healthBorder, SDL_MapRGB(surface->format, 200, 200, 200));

}

void Enemy::draw(SDL_Surface* surface){
    applySurface(getX(), getY(), animLib->get(animName)->getFrame(), surface, NULL);
    drawBorder(surface);
    drawHealthBar(surface);
}

void Enemy::fire(vector <GameObject*> &refObjects){
    int startX = static_cast<int>(rect.x+ (rect.w/2));
    int startY = static_cast<int>(rect.y+(rect.h));

    Uint32 diff = SDL_GetTicks() - lastFired;
    Uint32 limit = 400;

    if(diff > limit){
        Fire* f = new Fire(Fire::Types::ENEMY_BULLET,
                           animLib,
                           startX,
                           startY,
                           id);
        f->init();
        refObjects.insert(refObjects.begin(), f);
        lastFired = SDL_GetTicks();
    }
}

void Enemy::init(){
    animName = numberToString(t) + "-run";
    if(!animLib->has(animName)){
        if(t == (int) Enemy::Types::EATER){
            Animation* anim = new Animation(15, true);
            anim->addFrame("gfx/enemies/ball01.png", 2);
            anim->addFrame("gfx/enemies/ball02.png", 2);
            anim->addFrame("gfx/enemies/ball01.png", 2);
            anim->addFrame("gfx/enemies/ball02.png", 2);
            anim->addFrame("gfx/enemies/ball01.png",2);
            anim->addFrame("gfx/enemies/ball02.png", 2);
            anim->addFrame("gfx/enemies/ball01.png", 2);
            anim->addFrame("gfx/enemies/ball02.png");
            anim->addFrame("gfx/enemies/ball03.png");
            anim->addFrame("gfx/enemies/ball04.png");
            anim->addFrame("gfx/enemies/ball05.png");
            anim->addFrame("gfx/enemies/ball06.png");
            anim->addFrame("gfx/enemies/ball07.png");
            anim->addFrame("gfx/enemies/ball02.png");
            animLib->add(animName, anim);
        }
        else if(t == (int) Enemy::Types::DRUNK){
            Animation* anim = new Animation(10, true);
            anim->addFrame("gfx/enemies/drunk01.png");
            anim->addFrame("gfx/enemies/drunk02.png");
            anim->addFrame("gfx/enemies/drunk03.png");
            anim->addFrame("gfx/enemies/drunk04.png");
            anim->addFrame("gfx/enemies/drunk05.png");
            anim->addFrame("gfx/enemies/drunk06.png");
            anim->addFrame("gfx/enemies/drunk07.png");
            anim->addFrame("gfx/enemies/drunk08.png");
            anim->addFrame("gfx/enemies/drunk09.png");
            animLib->add(animName, anim);
        }
    }

    switch((Enemy::Types) t){
    case Enemy::Types::DRUNK:
        totalHealth = 90;
        triggerHappiness = 10;
        break;
    case Enemy::Types::EATER:
        totalHealth = 200;
        triggerHappiness = 5;
        break;
    default:
        totalHealth = 100;
    };
    health = totalHealth;

}

Enemy::~Enemy(){
    string s = objectType();
}
