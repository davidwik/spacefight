#ifndef __GAME__H__
#define __GAME__H__
#include "SDL/SDL.h"
#include "player.h"
#include "enemy.h"
#include "gameobject.h"
#include "animationlibrary.h"
#include <vector>

class Game {
private:
    static const int SCREEN_WIDTH = 800;
    static const int SCREEN_HEIGHT = 600;
    static const int SCREEN_BPP = 32;

    SDL_Surface* screen = NULL;
    SDL_Surface* background = NULL;
    std::vector<GameObject*> gameObjectList;
    void init();
    Player* player = NULL;
    AnimationLibrary* animLib = NULL;
    void setBackground();
    void gameLoop();
    void handleError(int e);
    Uint32 TimeLeft();

public:
    ~Game();
    SDL_Event event;
    void run();
};

#endif /* __GAME__H__ */
