#ifndef __GAME__H__
#define __GAME__H__
#include "SDL/SDL.h"
#include "SDL/SDL_ttf.h"
#include "player.h"
#include "constants.h"
#include "enemy.h"
#include "gameobject.h"
#include "animationlibrary.h"
#include <vector>

class Game {
private:
    SDL_Surface* screen = NULL;
    SDL_Surface* background = NULL;
    TTF_Font* font = NULL;
    SDL_Color textColor = {255, 255, 255};
    SDL_Surface* scoreBoard = NULL;
    std::vector<GameObject*> gameObjectList;
    void init();
    Player* player = NULL;
    AnimationLibrary* animLib = NULL;
    void cleanResources();
    void setBackground(std::string s);
    void gameLoop();
    int score = 0;
    void handleError(int e);
    Uint32 TimeLeft();
    bool initialized = false;
    int level = 1;
    Uint32 gameQuitsIn = 0;

public:
    enum class States { MENU, LEVEL, DEATH, WIN, QUIT };
    ~Game();
    void runState(Game::States t);
    void runMenu();
    void runLevel();
    void runDeath();
    void runWin();
    void initLevel();
    void switchState(Game::States t);
    void deleteObject(GameObject* go);
    SDL_Event event;
    void run();
};

#endif /* __GAME__H__ */
