#ifndef __PLAYER_H__
#define __PLAYER_H__
#include <string>
#include "SDL/SDL.h"
#include "gameobject.h"
#include "fire.h"
#include "constants.h"

using namespace std;

class Player: public GameObject {
private:
    int score;
    string name;
    bool fired = false;
    Uint32 lastFired = 0;

public:
    Player(int x, int y, AnimationLibrary* a);
    virtual ~Player();
    void addScore(int sc){ score += sc;}
    int getScore(){return score;}
    void update(vector <GameObject*> &refObjects);
    void draw(SDL_Surface* surface);
    void moveLeft();
    void moveRight();
    void moveUp();
    void fire(vector <GameObject*> &refObjects);
    void handleCollision(vector <GameObject*> gameObjectList);
    void moveDown();
    void listen(SDL_Event &event, vector <GameObject*> &refObjects);
    void init();
};

#endif /* __PLAYER_H__ */
