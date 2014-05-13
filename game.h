#ifndef __GAME__H__
#define __GAME__H__

#include "SDL/SDL.h"

class Game {
private:
    static const int SCREEN_WIDTH = 800;
    static const int SCREEN_HEIGHT = 600;
    static const int SCREEN_BPP = 32;

    SDL_Surface* screen = NULL;
    SDL_Surface* background = NULL;

    void init();
    void setBackground();
    void gameLoop();
    void handleError(int e);
    void waitForQuit();


public:
    void run();

};

#endif /* __GAME__H__ */
