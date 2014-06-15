#ifndef __ENEMY_H__
#define __ENEMY_H__
#include "animationlibrary.h"
#include "animation.h"
#include "gameobject.h"
#include "utils.h"
#include <string>

using namespace std;

class Enemy: public GameObject {

private:
    int health;
    int t;

public:
    enum class Types {EATER, DRUNK };


    Enemy(Enemy::Types type, AnimationLibrary* a, int x=0, int y=0) : GameObject(x, y, a){
        position.x = x;
        position.y = y;
        animLib = a;
        objType = "enemy";
        t = (int) type;
        printf("EN type: %d", t);
    }

    void update(SDL_Surface* surface);
    void init();
    void listen(SDL_Event event);

    Enemy::Types getType(){
        return (Enemy::Types) t;
    }
    virtual ~Enemy();


};

#endif /* __ENEMY_H__ */
