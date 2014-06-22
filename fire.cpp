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

void Fire::listen(SDL_Event event){}

void Fire::update(){}

void Fire::handleCollision(vector <GameObject*> gameObjectList){}

void Fire::draw(SDL_Surface* surface){}

void Fire::init(){}

Fire::~Fire(){}
