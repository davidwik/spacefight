#ifndef __PLAYER_H__
#define __PLAYER_H__
#include <string>
#include <vector>
#include "SDL/SDL.h"
#include "gameobject.h"
#include "fire.h"
#include "constants.h"
using namespace std;

class Player: public GameObject {
private:
    int score;
    string name;
    int totalHealth = 100;
    int health;
    int shieldHealth = 100;
    Uint32 shieldCoolDown = 0;
    bool shieldActive = false;
    bool fired = false;
    Uint32 lastFired = 0;
    int lives = 5;
    int ch = -1;
    //0vector <int> channelsInUse;
    void drawHP(SDL_Surface* surface);
    void drawHeartBar(SDL_Surface* surface);
    void drawShield(SDL_Surface* surface);
    void drawShieldBar(SDL_Surface* surface);
    void shieldOn();

public:
    Player(int x, int y, AnimationLibrary* a);
    virtual ~Player();
    void addScore(int sc){ score += sc;}
    int getScore(){return score;}
    void update(vector <GameObject*> &refObjects);
    void draw(SDL_Surface* surface);
    void moveLeft();
    void loseShield(int x);
    void moveRight();
    void moveUp();



    void loseHealth(int d){
        health -= d;
    }
    void fire(vector <GameObject*> &refObjects);
    void handleCollision(vector <GameObject*> gameObjectList, vector <GameObject*> &refObjects);
    void moveDown();
    void listen(SDL_Event &event, vector <GameObject*> &refObjects);
    void init();
};

#endif /* __PLAYER_H__ */
