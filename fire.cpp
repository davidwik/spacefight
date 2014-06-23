#include "fire.h"
using namespace std;

Fire::Fire(Fire::Types type,
           AnimationLibrary* a,
           int x,
           int y,
           int parent) : GameObject (x, y, a){
    position.x = x;
    position.y = y;
    animLib = a;
    objType = "fire";
    t = (int) type;
    parentId = parent;

    if(type == Fire::Types::PLAYER_BULLET){
        animName ="bullet-player";
        dy = -13;
    }
    else if(type == Fire::Types::ENEMY_BULLET){
        animName = "bullet-enemy";
        dy = 10;
    }

}

void Fire::listen(SDL_Event &event, vector <GameObject*> &refObjects){}

void Fire::update(vector <GameObject*> &refObjects){
    if(getY() < -100){
        terminate();
    }

    if(getY() > SCREEN_HEIGHT+100){
        terminate();
    }
    setY(getY()+dy);
    posUpdate();
}

void Fire::handleCollision(
    vector <GameObject*> gameObjectList,
    vector <GameObject *> &refObjects){
    for(auto it = gameObjectList.begin();
         it != gameObjectList.end();
        it++){
        if((Fire::Types) t == Fire::Types::ENEMY_BULLET){
            if((*it)->objectType() != "fire" && (*it)->objectType() != "enemy"){
                startExplosion((*it), refObjects);
                terminate();
            }
        }
        else if((Fire::Types) t == Fire::Types::PLAYER_BULLET){
            if((*it)->objectType() != "fire" && (*it)->objectType() != "player"){
            startExplosion((*it), refObjects);
            }
        }
    }

}

void Fire::startExplosion(GameObject* go, vector <GameObject*> &refObjects){
    go->posUpdate();

    SDL_Rect r = go->getRect();
    Explosion* e = new Explosion(
        Explosion::Types::MINI,
        animLib,
        static_cast<int>(r.x+(r.w/2)),
        static_cast<int>(r.y+(r.h/2))
    );

    e->init();
    //e->setSticky(go);
    terminate();
    refObjects.push_back(e);
}

void Fire::draw(SDL_Surface* surface){
    applySurface(getX(), getY(), animLib->get(animName)->getFrame(), surface, NULL);
    drawBorder(surface);
}

void Fire::init(){
    string an = "bullet-player";
    if(!animLib->has(an)){

            Animation *anim = new Animation(3, true);
            anim->addFrame("gfx/bullet01.png");
            anim->addFrame("gfx/bullet02.png");
            animLib->add(an, anim);

            Animation *b = anim->clone();
            an = "bullet-enemy";
            b->flipVertical();
            animLib->add(an, b);

    }
    setDamage(10);
}

Fire::~Fire(){
//    printf("Fire terminated!\n");
}
