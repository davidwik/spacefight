#ifndef __COLLISION_H__
#define __COLLISION_H__
#include <SDL/SDL.h>
#include "gameobject.h"
#include <vector>

class Collision {
public:
    void static runCollisionCheck(vector <GameObject*> &gameObjectList);
};

#endif /* __COLLISION_H__ */
