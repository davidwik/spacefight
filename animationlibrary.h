#ifndef __ANIMATION_LIBRARY_H__
#define __ANIMATION_LIBRARY_H__
#include "animation.h"
#include <map>
#include <string>

using namespace std;
class AnimationLibrary {
private:
    string lastKey;
    map <string, Animation* > library;

public:
    AnimationLibrary();
    ~AnimationLibrary();
    bool has(string key);
    void add(string key, Animation* animation);
    Animation* get(string key);
    void purge();
    void removeAnimation(string key);
};

#endif /*  __ANIMATION_LIBRARY_H__ */
