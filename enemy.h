#ifndef __ENEMY_H__
#define __ENEMY_H__
#include "animationlibrary.h"
#include "animation.h"
#include "gameobject.h"
#include "utils.h"
#include "fire.h"
#include "bonus.h"
#include <string>

using namespace std;

class Enemy: public GameObject {

private:
    int totalHealth;
    int health;
    int t;
    int dx;
    int dy;
    int points;
    short triggerHappiness = 0;
    Uint32 lastFired = 0;
    void drawHealthBar(SDL_Surface* surface);

public:
    enum class Types { EATER, DRUNK };

    Enemy(Enemy::Types type,
          AnimationLibrary* a,
          SoundLibrary* snd,
          int x=0,
          int y=0
    );

    void loseHealth(int h){
        health -= h;
        if(health <= 0){
            terminate();
        }
    }

    void update(vector <GameObject*> &refObjects);
    void fire(vector <GameObject*> &refObjects);
    int getPoints(){
        return points;
    }
    void draw(SDL_Surface* surface);
    void handleCollision(vector <GameObject*> gameObjectList, vector <GameObject*> &refObjects);
    void init();
    void listen(SDL_Event &event, vector <GameObject*> &refObjects);

    Enemy::Types getType(){
        return (Enemy::Types) t;
    }

    virtual ~Enemy();

};

#endif /* __ENEMY_H__ */
