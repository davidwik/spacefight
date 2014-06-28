#include "gameobject.h"

int GameObject::counter = 0;

GameObject::~GameObject(){
/*    animLib = std::null_ptr;
      soundLib = std::null_ptr;*/
}

GameObject::GameObject(int startPosX, int startPosY, AnimationLibrary* a){
    position.x = startPosX;
    position.y = startPosY;
    animLib = a;
    id = counter;
    counter++;
}

void GameObject::posUpdate(){
    rect.w = getWidth();
    rect.h = getHeight();
    rect.x = getX();
    rect.y = getY();
}


int GameObject::getWidth(){
    SDL_Surface* m = NULL;
    try {
        m = (SDL_Surface*) animLib->get(animName)->getFrame();
    }
    catch(int e){
        return 0;
    }
    return m->w;
}

void GameObject::setSoundLibrary(SoundLibrary* snd){
    // Attach the soundlib if it's not already attached
    if(soundLib != NULL){
        soundLib = snd;
    }
}

SDL_Rect GameObject::getRect(){
    return rect;
}

void GameObject::drawBorder(SDL_Surface* screen){
    if(DRAW_BORDERS && colliding){
        SDL_Rect topBar = {
            static_cast<Sint16>(rect.x),
            static_cast<Sint16>(rect.y),
            static_cast<Uint16>(rect.w),
            static_cast<Uint16>(BORDER_WIDTH)
        };

        SDL_Rect bottomBar = {
            static_cast<Sint16>(rect.x),
            static_cast<Sint16>(rect.y+rect.h-BORDER_WIDTH),
            static_cast<Uint16>(rect.w),
            static_cast<Uint16>(BORDER_WIDTH)
        };

        SDL_Rect leftBar = {
            static_cast<Sint16>(rect.x),
            static_cast<Sint16>(rect.y),
            static_cast<Uint16>(BORDER_WIDTH),
            static_cast<Uint16>(rect.h)
        };

        SDL_Rect rightBar = {
            static_cast<Sint16>(rect.x+rect.w-BORDER_WIDTH),
            static_cast<Sint16>(rect.y),
            static_cast<Uint16>(BORDER_WIDTH),
            static_cast<Uint16>(rect.h)
        };

        SDL_FillRect(
            screen,
            &topBar,
            SDL_MapRGB(screen->format,255, 0, 0)
        );

        SDL_FillRect(
            screen,
            &bottomBar,
            SDL_MapRGB(screen->format,255, 0, 0)
        );

        SDL_FillRect(
            screen,
            &leftBar,
            SDL_MapRGB(screen->format,255, 0, 0)
        );

        SDL_FillRect(
            screen,
            &rightBar,
            SDL_MapRGB(screen->format,255, 0, 0)
        );
    }
}


int GameObject::getHeight(){
    SDL_Surface* m = NULL;
    try {
        m = (SDL_Surface*) animLib->get(animName)->getFrame();
    }
    catch(int e){
        return 0;
    }
    return m->h;
}
