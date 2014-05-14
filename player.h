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
    void addScore(int sc){ score += sc;}
    int getScore(){return score;}
    Player(void){ score = 0; name = "Uknown player";}
    Player(string n){ score = 0; name = n;}
    string getName(){ return name;}
    ~Player(){ printf("Goodbye..\n");}

};

#endif /* __PLAYER_H__ */
