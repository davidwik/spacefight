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
        printf("EnemyType: %d\n", t);
        printf("ObjectId: %d\n", id);

}

void Enemy::listen(SDL_Event event){
    ;
}

void Enemy::update(){
    if(position.x > SCREEN_W){
        dx = ~dx+1;
        position.x = SCREEN_W-1;
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

    if(position.y > (int) SCREEN_H/2){
        dy = ~dy+1;
    }
    if(position.y < 0){
        dy = ~dy+1;
    }

    position.x += dx;
    position.y += dy;
}

void Enemy::collCheck(vector <GameObject*> &gameObjectList){}

void Enemy::draw(SDL_Surface* surface){
    applySurface(getX(), getY(), animLib->get(animName)->getFrame(), surface, NULL);
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
}

Enemy::~Enemy(){
    string s = objectType();
    printf("Destroying instance of %s - GameObjectId:%d \n ", (const char*) s.c_str(), id);
}
