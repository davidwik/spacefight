#ifndef __PLAYER_H__
#define __PLAYER_H__
#include "SDL/SDL.h"

class Player {
protected:
    struct pos {
        int x;
        int y;
    } p;

public:
    /*  pos getPos(void){
        return pos;
    }
    */
    int getX(){ return p.x;}
    int getY(){ return p.y;}
    void setX(int x){ p.x = x;}
    void setY(int y){ p.y = y;}
};




#endif /* __PLAYER_H__ */
