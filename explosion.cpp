#include "explosion.h"
using namespace std;

Explosion::Explosion(Explosion::Types type,
           AnimationLibrary* a,
           int x,
           int y) : GameObject (x, y, a){
    position.x = x;
    position.y = y;
    animLib = a;
    objType = "explosion";
    t = (int) type;

    if(t == (int) Explosion::Types::MINI){
        int r = rand()%3;
        if(r > 3){
            r = 2;
            printf("BUU wrong\n");
        }
        animName = "mini-explosion-" + numberToString(r);
        ticksToLive = SDL_GetTicks() + 500;
    }
    else {
        animName = "big-explosion";
        ticksToLive = SDL_GetTicks() + 1000;
    }
}

void Explosion::listen(
    SDL_Event &event,
    vector <GameObject*> &refObjects
){}

void Explosion::handleCollision(vector <GameObject*> gameObjectList, vector <GameObject*> &refObjects){

}

void Explosion::draw(SDL_Surface* surface){
    applySurface(getX(), getY(), animLib->get(animName)->getFrame(), surface, NULL);
    drawBorder(surface);
}

void Explosion::setSticky(GameObject *go){

}

void Explosion::update(vector <GameObject*> &refObjects){

}

void Explosion::init(){
    if(t == (int) Explosion::Types::MINI){
        if(!animLib->has("mini-explosion-0")){
            Animation* a = new Animation(20, true);
            a->addFrame("res/gfx/sprites/explosion-mini01.png");
            a->addFrame("res/gfx/sprites/explosion-mini02.png");
            a->addFrame("res/gfx/sprites/explosion-mini03.png");
            a->addFrame("res/gfx/sprites/explosion-mini04.png");
            a->addFrame("res/gfx/sprites/explosion-mini05.png");
            a->addFrame("res/gfx/sprites/explosion-mini06.png");
            animLib->add("mini-explosion-0", a);

            Animation* b = a->clone();
            b->flipVertical();
            animLib->add("mini-explosion-1", b);

            Animation* c = a->clone();
            c->flipHorizontal();
            animLib->add("mini-explosion-2", c);

            Animation* d = b->clone();
            d->flipHorizontal();
            animLib->add("mini-explosion-3", d);



        }
        if(soundLib != NULL){
            if(!soundLib->has("hit")){
                soundLib->add(
                    "hit",
                    new Sound(
                        "res/audio/hit.ogg",
                        Sound::Types::EFFECT,
                        4
                    )
                );
            }
            try {
                soundLib->play("hit", 0);
            } catch(int e){
                ;
            }
        }

        if(!animLib->has("big-explosion")){
            Animation* q = new Animation(20, true);
            q->addFrame("res/gfx/sprites/explosion-big01.png");
            q->addFrame("res/gfx/sprites/explosion-big02.png");
            q->addFrame("res/gfx/sprites/explosion-big03.png");
            q->addFrame("res/gfx/sprites/explosion-big04.png");
            q->addFrame("res/gfx/sprites/explosion-big05.png");
            q->addFrame("res/gfx/sprites/explosion-big06.png");
            q->addFrame("res/gfx/sprites/explosion-big07.png");
            animLib->add("big-explosion", q);
        }
    }
    else if(t == (int) Explosion::Types::BIG){
        if(soundLib != NULL){
            if(!soundLib->has("ship-explosion")){
                soundLib->add("ship-explosion",
                              new Sound(
                                  "res/audio/explosion.ogg",
                                  Sound::Types::EFFECT,
                                  10
                              )
                );
            }

            try {
                soundLib->play("ship-explosion", 0);
            } catch(int e){
                ;
            }
        }
    }

}

Explosion::~Explosion(){
    sticky = NULL;
    animLib = NULL;
}
