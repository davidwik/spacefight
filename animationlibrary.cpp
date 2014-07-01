#include "animationlibrary.h"
#include <iostream>
using namespace std;

AnimationLibrary::AnimationLibrary(){
}

AnimationLibrary::~AnimationLibrary(){
    for(unordered_map <string, Animation*>::iterator it = library.begin();
        it != library.end();
        it++){
        delete (it->second);
    }
    library.clear();

}

void AnimationLibrary::purge(){

    for(unordered_map <string, Animation*>::iterator it = library.begin();
        it != library.end();
        it++){
        delete (it->second);
    }
    library.clear();
}

bool AnimationLibrary::has(string key){
    return (library.count(key) > 0) ? true : false;
}

Animation* AnimationLibrary::get(string key){
    if(!has(key)){
        throw MISSING_INDEX;
    }
    return library[key];
}

void AnimationLibrary::remove(string key){
    if(has(key)){
        unordered_map <string, Animation*>::iterator it;
        it = library.find(key);
        delete (it->second);
        library.erase(it);
    }
}

void AnimationLibrary::add(string key, Animation* animation){
    // First do a lookup on the map and see
    // whether it's already set.
    if(!has(key)){
        library[key] = animation;
    }
}
