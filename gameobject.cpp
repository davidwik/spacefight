#include "gameobject.h"

GameObject::~GameObject(){
    // Cleaning up animations
    for(std::map<string, Animation*>::iterator animMapIter=animations.begin();
        animMapIter!=animations.end();
        animMapIter++){
        delete animMapIter->second;
    }
    printf("GameObject destroyed\n");
}
