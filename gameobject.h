#ifndef __GAMEOBJECT_H__
#define __GAMEOBJECT_H__
#define BORDER_WIDTH 1
#include <SDL/SDL.h>
#include <string>
#include <vector>
#include "constants.h"
#include "utils.h"
#include "errorcodes.h"
#include "animationlibrary.h"
#include "soundlibrary.h"

using namespace std;
class GameObject {

protected:
    struct pos {
        int x, y;
    } position;
    string objType;
    string animName;
    int id;
    Uint32 ticksToLive = 0;
    int damage;
    bool termination = false;
    bool colliding = false;
    int stopForMs = 0;
    int parentId = -1;
    SDL_Rect rect;
    AnimationLibrary* animLib = NULL;
    SoundLibrary* soundLib = NULL;

public:
    int zIndex = 0;
    static int counter;
    std::string objectType(void){
        return objType;
    };

    bool operator< (const GameObject &other) const {
        return zIndex > other.zIndex;
    }

    void setXY(int x, int y) {
        position.x = x;
        position.y = y;
    }

    GameObject(int startPosX, int startPosY, AnimationLibrary* a, SoundLibrary* snd);

    int getZIndex(){
        return zIndex;
    }

    void setX(int x){position.x = x;}
    void setY(int y){position.y = y;}
    void terminate(){ termination = true;}
    int getWidth();
    int getHeight();
    void stopFor(int ms){ stopForMs = ms;}
    int getId() {
        return id;
    }

    bool killMe(){
        if(ticksToLive != 0 && ticksToLive < SDL_GetTicks()){
            return true;
        }
        else {
            return termination;
        }
    }

    virtual void listen(SDL_Event &event, vector <GameObject*> &refObjects) = 0;
    virtual void init(void) = 0;
    virtual void update(vector <GameObject*> &refObjects) = 0;

    int getDamage() { return damage;}
    SDL_Rect getRect();

    virtual void handleCollision(vector <GameObject*> gameObjectList, vector <GameObject*> &refObjects) = 0;
    virtual void draw(SDL_Surface* screen) = 0;
    bool isColliding(){return colliding;}
    void setCollision(bool val){
        colliding = val;
    }
    void drawBorder(SDL_Surface* screen);
    void posUpdate();
    int getX(){ return position.x;}
    int getY(){ return position.y;}
    int getParentId(){return parentId;}
    pos getPosition(){return position;}


    ~GameObject();
};

bool gameObjectSort(const GameObject* s1, const GameObject* s2);

#endif /* __GAMEOBJECT_H__ */
