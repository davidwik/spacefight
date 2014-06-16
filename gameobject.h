#ifndef __GAMEOBJECT_H__
#define __GAMEOBJECT_H__
#include <SDL/SDL.h>
#include <string>
#include <vector>
#include "utils.h"
#include "animationlibrary.h"
using namespace std;
class GameObject {

protected:
    struct pos {
        int x, y;
    } position;
    string objType;
    string animName;
    int id;
    AnimationLibrary* animLib;

public:
    static int counter;
    std::string objectType(void){
        return objType;
    };

    void setXY(int x, int y) {
        position.x = x;
        position.y = y;
    }
    GameObject(int startPosX, int startPosY, AnimationLibrary* a);

    void setX(int x){position.x = x;}
    void setY(int y){position.y = y;}
    virtual void listen(SDL_Event event) = 0;
    virtual void init(void) = 0;
    virtual void update() = 0;
    virtual void collCheck(vector <GameObject*> &gameObjectList) = 0;
    virtual void draw(SDL_Surface* screen) = 0;
    int getX(){ return position.x;}
    int getY(){ return position.y;}
    pos getPosition(){return position;}
    ~GameObject();
};

#endif /* __GAMEOBJECT_H__ */
