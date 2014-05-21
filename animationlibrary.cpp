#include "animationlibrary.h"
#include <iostream>
using namespace std;

AnimationLibrary::AnimationLibrary(){
}

AnimationLibrary::~AnimationLibrary(){
    printf("Freeing AnimationLibrary..\n");
    for(map <string, Animation*>::iterator it = library.begin();
        it != library.end();
        it++){
        printf("Freeing animation \"%s\"\n", it->first.c_str());
        delete (it->second);
    }
    library.clear();

}

void AnimationLibrary::purge(){

    for(map <string, Animation*>::iterator it = library.begin();
        it != library.end();
        it++){
        printf("Freeing animation \"%s\"\n", it->first.c_str());
        delete (it->second);
    }
    library.clear();
}

bool AnimationLibrary::has(string key){
    return (library.find(key) == library.end()) ? false : true;
}

Animation* AnimationLibrary::get(string key){
    return library[key];
}

void AnimationLibrary::add(string key, Animation* animation){
    // First do a lookup on the map and see
    // whether it's already set.
    library[key] = animation;
}
