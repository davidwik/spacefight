#ifndef __GAMEOBJECT_H__
#define __GAMEOBJECT_H__
#include <SDL/SDL.h>
#include <map>
#include "animation.h"
class GameObject {
protected:
    struct pos {
        int x, y;
    } position;

    std::map <string, Animation*> animations;
    std::map <string, Animation*>::iterator animMapIter;
    string animName;
public:
    void setXY(int x, int y) {
        position.x =x;
        position.y=y;
    }
    GameObject(int startPosX, int startPosY) {
        position.x = startPosX;
        position.y = startPosY;
    }
    void setX(int x){position.x = x;}
    void setY(int y){position.y = y;}
    void addAnimation(Animation* anim, string name);
    virtual void listen(SDL_Event event) = 0;
    virtual void init(void) = 0;
    int getX(){ return position.x;}
    int getY(){ return position.y;}
    pos getPosition(){return position;}
    ~GameObject();
};

#endif /* __GAMEOBJECT_H__ */
