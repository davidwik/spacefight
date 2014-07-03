#include "bonus.h"
using namespace std;

Bonus::Bonus(AnimationLibrary* a,
             SoundLibrary* snd,
             int x,
             int y) : GameObject (x, y, a, snd){
    position.x = x;
    position.y = y;
    animLib = a;
    soundLib = snd;
    objType = "bonus";
    counter = 0.00f;
    increase = I_AM_PI / 50;
    srand(time(0));
    int chance = rand()%3;
    chance++;
    setupType(chance);
    zIndex = 3;
}



void Bonus::setupType(int type){
    switch(static_cast<Bonus::Types>(type)){
    case Bonus::Types::HEART:
        t = type;
        animName = "bonus-heart";
        break;

    case Bonus::Types::AMMO:
        t = type;
        animName = "bonus-ammo";
        break;

    case Bonus::Types::SHIELD:
        t = type;
        animName = "bonus-shield";
        break;

    default:
        break;
    }

}

void Bonus::listen(SDL_Event &event, vector <GameObject*> &refObjects){}

void Bonus::update(vector <GameObject*> &refObjects){
    posUpdate();
    if(getY() > SCREEN_HEIGHT+100){
        terminate();
    }
    double the_x = cos(counter);
    counter += increase;

    position.x += (int) (the_x*20);

    position.y += 3;
    posUpdate();
}

void Bonus::handleCollision(
    vector <GameObject*> gameObjectList,
    vector <GameObject *> &refObjects){}

void Bonus::draw(SDL_Surface* surface){
    applySurface(getX(), getY(), animLib->get(animName)->getFrame(), surface, NULL);
    drawBorder(surface);
}


void Bonus::init(){

    if(!animLib->has("bonus-heart")){
        Animation *anim = new Animation(10, true);
        anim->addFrame("res/gfx/sprites/bonus-heart01.png");
        anim->addFrame("res/gfx/sprites/bonus-heart02.png");
        anim->addFrame("res/gfx/sprites/bonus-heart03.png");
        animLib->add("bonus-heart", anim);
    }

    if(!animLib->has("bonus-shield")){
        Animation *b = new Animation(10, true);
        b->addFrame("res/gfx/sprites/bonus-shield01.png");
        b->addFrame("res/gfx/sprites/bonus-shield02.png");
        b->addFrame("res/gfx/sprites/bonus-shield03.png");
        animLib->add("bonus-shield", b);
    }

    if(!animLib->has("bonus-ammo")){
        Animation *c = new Animation(10, true);
        c->addFrame("res/gfx/sprites/bonus-ammo01.png");
        c->addFrame("res/gfx/sprites/bonus-ammo02.png");
        c->addFrame("res/gfx/sprites/bonus-ammo03.png");
        animLib->add("bonus-ammo", c);
    }

    if(soundLib != NULL){
        if(!soundLib->has("bonus")){
            soundLib->add(
                "bonus",
                new Sound(
                    "res/audio/bonus.ogg",
                    Sound::Types::EFFECT,
                    6
                )
            );
        }
    }
}


Bonus::~Bonus(){}
