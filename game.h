#ifndef __GAME__H__
#define __GAME__H__
#include "SDL/SDL.h"
#include "player.h"

class Game {
private:
    static const int SCREEN_WIDTH = 800;
    static const int SCREEN_HEIGHT = 600;
    static const int SCREEN_BPP = 32;

    SDL_Surface* screen = NULL;
    SDL_Surface* background = NULL;
    SDL_Event event;
    void init();
    Player* player = NULL;
    void setBackground();
    void gameLoop();
    void handleError(int e);
    void waitForQuit(int ms);
    Uint32 TimeLeft();

public:
    void run();
};

#endif /* __GAME__H__ */
