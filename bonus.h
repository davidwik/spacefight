#ifndef __BONUS_H__
#define __BONUS_H__
#include <string>
#include <SDL/SDL.h>
#include <vector>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include "utils.h"
#include "gameobject.h"
#include "animation.h"
#include "animationlibrary.h"

using namespace std;

class Bonus: public GameObject {

private:
    double counter;
    double increase;
    int t;
    int dy;
    int dx;
    int value;

    void setupType(int i);

public:
    enum class Types { HEART=1,SHIELD,AMMO};

    Bonus(AnimationLibrary* a,
          SoundLibrary* snd,
          int x=0,
          int y=0
    );

    int getValue(){
        return value;
    }

    void playSound();

    void update(vector <GameObject*> &refObjects);
    void draw(SDL_Surface* screen);

    void handleCollision(vector <GameObject*> gameObjectList, vector <GameObject*> &refObjects);
    void init();
    void listen(SDL_Event &event, vector <GameObject*> &refObjects);

    Bonus::Types getType(){
        return (Bonus::Types) t;
    }

    virtual ~Bonus();
};

#endif /* __BONUS_H__ */
