#include "fire.h"
using namespace std;

Fire::Fire(Fire::Types type,
           AnimationLibrary* a,
           int x,
           int y,
           int parent) : GameObject (x, y, a){
    position.x = x;
    position.y = y;
    animLib = a;
    objType = "fire";
    t = (int) type;
    parentId = parent;

    if(type == Fire::Types::BULLET && parentId == 0){
        animName = numberToString(t) + "-player";
        dy = -13;
    }
    else if(type == Fire::Types::BULLET && parentId != 0){
        animName = numberToString(t) + "-enemy";
        dy = 10;
    }

}

void Fire::listen(SDL_Event &event, vector <GameObject*> &refObjects){}

void Fire::update(vector <GameObject*> &refObjects){
    if(getY() < -100){
        terminate();
    }

    if(getY() > SCREEN_HEIGHT+100){
        terminate();
    }

    setY(getY()+dy);
    posUpdate();
}

void Fire::handleCollision(vector <GameObject*> gameObjectList){

}

void Fire::draw(SDL_Surface* surface){
    applySurface(getX(), getY(), animLib->get(animName)->getFrame(), surface, NULL);
    drawBorder(surface);
}

void Fire::init(){
    string an = numberToString(t) + "-player";
    if(!animLib->has(an)){
        if( t == (int) Fire::Types::BULLET){
            Animation *anim = new Animation(3, true);
            anim->addFrame("gfx/bullet01.png");
            anim->addFrame("gfx/bullet02.png");
            animLib->add(an, anim);
            an = numberToString(t) + "-enemy";
            Animation *b = anim->clone();
            b->flipVertical();
            animLib->add(an, b);
        }
    }
    setDamage(10);
}

Fire::~Fire(){
//    printf("Fire terminated!\n");
}
