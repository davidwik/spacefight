#ifndef __PLAYER_H__
#define __PLAYER_H__
#include <string>
#include "SDL/SDL.h"
#include "gameobject.h"

using namespace std;

class Player: public GameObject {
private:
    int score;
    string name;

public:
    Player(int x, int y, AnimationLibrary* a) : GameObject(x, y, a){
        position.x = x;
        position.y = y;
        animLib = a;
        objType = "player";
    }
    virtual ~Player();
    void addScore(int sc){ score += sc;}
    int getScore(){return score;}
    void update(SDL_Surface* surface);
    void moveLeft();
    void moveRight();
    void moveUp();
    void moveDown();
    void listen(SDL_Event event);
    void init();
};

#endif /* __PLAYER_H__ */
