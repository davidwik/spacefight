#ifndef __GAMEOBJECT_H__
#define __GAMEOBJECT_H__
#define BORDER_COLOR 0xff0000
#define BORDER_WIDTH 1
#include <SDL/SDL.h>
#include <string>
#include <vector>
#include "constants.h"
#include "utils.h"
#include "errorcodes.h"
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
    int damage;
    bool colliding = false;
    SDL_Rect rect;
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
    int getWidth();
    int getHeight();
    int getId() {
        return id;
    }
    virtual void listen(SDL_Event event) = 0;
    virtual void init(void) = 0;
    virtual void update() = 0;
    int getDamage() { return damage;}
    SDL_Rect getRect();
    virtual void handleCollision(vector <GameObject*> gameObjectList) = 0;
    virtual void draw(SDL_Surface* screen) = 0;
    bool isColliding(){return colliding;}
    void setCollision(bool val){
        colliding = val;
    }
    void drawBorder(SDL_Surface* screen);
    void posUpdate();
    int getX(){ return position.x;}
    int getY(){ return position.y;}
    pos getPosition(){return position;}
    ~GameObject();
};

#endif /* __GAMEOBJECT_H__ */
