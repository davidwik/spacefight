#include "fire.h"
using namespace std;

Fire::Fire(Fire::Types type,
           AnimationLibrary* a,
           SoundLibrary* snd,
           int x,
           int y,
           int parent) : GameObject (x, y, a, snd){
    position.x = x;
    position.y = y;
    animLib = a;
    soundLib = snd;
    objType = "fire";
    t = (int) type;
    parentId = parent;
    dx = 0;

    zIndex = 0;
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
    setX(getX()+dx);
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
            if((*it)->objectType() == "player"){
                startExplosion((*it), refObjects);
                terminate();
            }
        }
        else if((Fire::Types) t == Fire::Types::PLAYER_BULLET){
            if((*it)->objectType() == "enemy"){
                startExplosion((*it), refObjects);
            }
        }
    }
}

void Fire::startExplosion(GameObject* go, vector <GameObject*> &refObjects){
    int y = getY();
    go->posUpdate();
    if((Fire::Types) t == Fire::Types::ENEMY_BULLET){
        y -= (dy*5);
    }
    else {
        y = go->getY();
    }

    Explosion* e = new Explosion(
        Explosion::Types::MINI,
        animLib,
        soundLib,
        getX(),
        y
    );

    e->init();
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
            anim->addFrame("res/gfx/sprites/bullet01.png");
            anim->addFrame("res/gfx/sprites/bullet02.png");
            animLib->add(an, anim);

            Animation *b = anim->clone();
            an = "bullet-enemy";
            b->flipVertical();
            animLib->add(an, b);

    }

    if(soundLib != NULL){
        if(!soundLib->has("fire")){
            soundLib->add("fire", new Sound("res/audio/fire.ogg", Sound::Types::EFFECT, 10));
        }
        try {
            soundLib->play("fire", 0);
        } catch(int e){
            printf("NO SOUND..");
        }
    }

    setDamage(10);
}

Fire::~Fire(){
//    printf("Fire terminated!\n");
}
