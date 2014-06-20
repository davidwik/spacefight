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
    int dx;
    int dy;

public:
    enum class Types {EATER, DRUNK };

    Enemy(Enemy::Types type,
          AnimationLibrary* a,
          int x=0,
          int y=0);

    void update();
    void draw(SDL_Surface* surface);
    void handleCollision(vector <GameObject*> gameObjectList);
    void init();
    void listen(SDL_Event event);

    Enemy::Types getType(){
        return (Enemy::Types) t;
    }

    virtual ~Enemy();


};

#endif /* __ENEMY_H__ */
