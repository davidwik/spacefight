#ifndef __PLAYER_H__
#define __PLAYER_H__
#include <string>
#include <vector>
#include "SDL/SDL.h"
#include "gameobject.h"
#include "fire.h"
#include "bonus.h"
#include "constants.h"
using namespace std;

class Player: public GameObject {
private:
    int score;
    string name;
    int totalHealth;
    int health;
    int shieldHealth;
    int shieldHealthTotal;
    Uint32 shieldCoolDown;
    bool shieldActive;
    bool fired;
    Uint32 lastFired;
    int lives;
    int ammoType;
    Uint32 specialAmmoUntil;

    //0vector <int> channelsInUse;
    void drawHP(SDL_Surface* surface);
    void drawHeartBar(SDL_Surface* surface);
    void drawShield(SDL_Surface* surface);
    void drawShieldBar(SDL_Surface* surface);
    void shieldOn();

public:
    Player(int x, int y, AnimationLibrary* a, SoundLibrary* snd);
    enum class AmmoTypes { SINGLE, TRIPLE};

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
