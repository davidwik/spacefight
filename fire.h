#ifndef __FIRE_H__
#define __FIRE_H__
#include <string>
#include <SDL/SDL.h>
#include <vector>
#include "utils.h"
#include "gameobject.h"
#include "animation.h"
#include "animationlibrary.h"
using namespace std;

class Fire: public GameObject {

private:
    int t;
    int dy;
    int dx;
    int damage;

public:
    enum class Types { BULLET, ROCKET, LASER };

    Fire(Fire::Types type,
         AnimationLibrary* a,
         int x=0,
         int y=0,
         int parent=-1
    );

    void setDX(int directionX){
        dx = directionX;
    }

    void setDY(int directionY){
        dy = directionY;
    }

    void setDamage(int d){
        damage = d;
    }

    int getDamage(){
        int tmp = damage;
        damage = 0;
        return tmp;
    }
    void update(vector <GameObject*> &refObjects);
    void draw(SDL_Surface* screen);
    void handleCollision(vector <GameObject*> gameObjectList);
    void init();
    void listen(SDL_Event &event, vector <GameObject*> &refObjects);

    Fire::Types getType(){
        return (Fire::Types) t;
    }

    virtual ~Fire();
};

#endif /* __FIRE_H__ */
