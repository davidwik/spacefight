#include "enemy.h"
#include <iostream>
#include <string>

using namespace std;
void Enemy::listen(SDL_Event event){
    ;
}

void Enemy::update(SDL_Surface* surface){
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
    printf("Killing enemy\n");
}
