#include "gameobject.h"

int GameObject::counter = 0;

GameObject::~GameObject(){

}

GameObject::GameObject(int startPosX, int startPosY, AnimationLibrary* a){

    position.x = startPosX;
    position.y = startPosY;
    animLib = a;
    id = counter;
    counter++;
}
