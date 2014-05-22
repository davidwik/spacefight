#include "animationlibrary.h"
#include <iostream>
using namespace std;

AnimationLibrary::AnimationLibrary(){
}

AnimationLibrary::~AnimationLibrary(){
    printf("Freeing AnimationLibrary..\n");
    for(unordered_map <string, Animation*>::iterator it = library.begin();
        it != library.end();
        it++){
        printf("Freeing animation \"%s\"\n", it->first.c_str());
        delete (it->second);
    }
    library.clear();

}

void AnimationLibrary::purge(){

    for(unordered_map <string, Animation*>::iterator it = library.begin();
        it != library.end();
        it++){
        printf("Freeing animation \"%s\"\n", it->first.c_str());
        delete (it->second);
    }
    library.clear();
}

bool AnimationLibrary::has(string key){
    return (library.count(key) > 0) ? true : false;
}

Animation* AnimationLibrary::get(string key){
    if(!has(key)){
        throw ANIMATION_EXCEPTION;
    }
    return library[key];
}

void AnimationLibrary::remove(string key){
    if(has(key)){
        unordered_map <string, Animation*>::iterator it;
        it = library.find(key);
        printf("Freeing animation \"%s\"\n", it->first.c_str());
        delete (it->second);
        library.erase(it);
    }
}

void AnimationLibrary::add(string key, Animation* animation){
    // First do a lookup on the map and see
    // whether it's already set.
    library[key] = animation;
}
