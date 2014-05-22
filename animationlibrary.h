#ifndef __ANIMATION_LIBRARY_H__
#define __ANIMATION_LIBRARY_H__
#include "animation.h"
#include <unordered_map>
#include <string>
#include "errorcodes.h"
using namespace std;
class AnimationLibrary {

private:
    string lastKey;
    unordered_map <string, Animation* > library;

public:
    AnimationLibrary();
    ~AnimationLibrary();
    bool has(string key);
    void add(string key, Animation* animation);
    Animation* get(string key);
    void purge();
    void remove(string key);
};

#endif /*  __ANIMATION_LIBRARY_H__ */
