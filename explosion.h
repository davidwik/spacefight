#ifndef __EXPLOSION_H__
#define __EXPLOSION_H__
#include <string>
#include <SDL/SDL.h>
#include <vector>
#include "utils.h"
#include "gameobject.h"
#include "animation.h"
#include "animationlibrary.h"
using namespace std;

class Explosion: public GameObject {

private:
    int t;
    GameObject* sticky = NULL;

public:
    enum class Types { BIG, MINI };

    Explosion(Explosion::Types type,
         AnimationLibrary* a,
         int x=0,
         int y=0
    );


    void setSticky(GameObject *gameObject);

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
    void handleCollision(vector <GameObject*> gameObjectList, vector <GameObject*> &refObjects);
    void init();
    void listen(SDL_Event &event, vector <GameObject*> &refObjects);

    Explosion::Types getType(){
        return (Explosion::Types) t;
    }

    virtual ~Explosion();
};

#endif /* __EXPLOSION_H__ */
