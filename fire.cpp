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

}

void Fire::listen(SDL_Event &event, vector <GameObject*> &refObjects){}

void Fire::update(vector <GameObject*> &refObjects){
    if(getY() < -100){
        terminate();
    }

    setY(getY()+dy);

}

void Fire::handleCollision(vector <GameObject*> gameObjectList){}

void Fire::draw(SDL_Surface* surface){
    drawBorder(surface);
    applySurface(getX(), getY(), animLib->get(animName)->getFrame(), surface, NULL);

}

void Fire::init(){
    animName = numberToString(t) + "-player";
    if(!animLib->has(animName)){
        if( t == (int) Fire::Types::BULLET){
            Animation *anim = new Animation(3, true);
            anim->addFrame("gfx/bullet01.png");
            anim->addFrame("gfx/bullet02.png");
            animLib->add(animName, anim);
        }
    }
    dx = 0;
    dy = -2;
}

Fire::~Fire(){
    printf("Fire terminated!\n");
}
