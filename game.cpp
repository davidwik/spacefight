#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include <cstdlib>
#include <cmath>
#include "utils.h"
#include "game.h"
#include "fire.h"
#include "errorcodes.h"
#include "constants.h"
#include "collision.h"
#include <typeinfo>
#include <iostream>
#include <string>
#include <algorithm>

#include "explosion.h"

void Game::run(){
    try {
        init();
        gameLoop();
    } catch(int e){
        handleError(e);
    }

}


void Game::runState(Game::States t){
    if(!initialized){
        init(); // Set up game specifics.
    }

    switch(t){
    case Game::States::LEVEL:
        runLevel();
        break;

    case Game::States::MENU:
        runMenu();
        break;

    default:
        runLevel();

    }
}

void Game::deleteObject(GameObject* go){
    if(go->objectType() == "player"){
        delete static_cast<Player*>(go);
    }
    else if(go->objectType() == "enemy"){
        delete static_cast<Enemy*>(go);
    }
    else if(go->objectType() == "fire"){
        delete static_cast<Fire*>(go);
    }
    else if(go->objectType() == "explosion"){
        delete static_cast<Explosion*>(go);
    }
    else {
        printf("WHAT?!");
    }
    go = NULL;
}

Game::~Game(){
    printf("Running Game deconstructor!\n");
    for(vector <GameObject*>::iterator it = gameObjectList.begin();
        it != gameObjectList.end();
        it++){
        deleteObject((*it));
        (*it) = NULL;
    }
    gameObjectList.empty();
    SDL_FreeSurface(screen); // Should maybe be removed?
    gameObjectList.clear();
    printf("Qutting SDL\n");
    SDL_Quit();
    printf("Returning to main!\n");
}

void Game::cleanResources(){
    for(vector <GameObject*>::iterator it = gameObjectList.begin();
        it != gameObjectList.end();
        it++){
        deleteObject((*it));
        (*it) = NULL;
    }
    gameObjectList.empty();
    SDL_FreeSurface(background);
    SDL_FreeSurface(scoreBoard);
    gameObjectList.clear();
}


void Game::init(){
    if(SDL_Init(SDL_INIT_EVERYTHING) == -1){
        throw SDL_INIT_ERROR;
    }

    screen = SDL_SetVideoMode(SCREEN_WIDTH,
                              SCREEN_HEIGHT,
                              SCREEN_BPP,
                              SDL_HWSURFACE | SDL_DOUBLEBUF);
    if(screen == NULL){
        throw SDL_SCREEN_ERROR;
    }

    // Init font
    if(TTF_Init() == -1){
        throw SDL_FONT_ERROR;
    }

    font = TTF_OpenFont("gfx/digifat.ttf", 20);

    if(font == NULL ){
        printf("Failed to open font");
    }

    SDL_WM_SetCaption("Spaaace Fight!", NULL);
    initialized = true;
    animLib = new AnimationLibrary();

}


void Game::initLevel(){
    gameObjectList.reserve(1000);

    if(player == NULL){
        player = new Player(400, 300, animLib);
        gameObjectList.push_back(player);
    }
    // Add all start objects

    int drunk = level*2;
    int eat = static_cast<int>(floor(level*1.5));
    for(int i = 0; i < drunk; i++){
        gameObjectList.push_back(new Enemy(Enemy::Types::DRUNK, animLib, 100, 40));
    }

    for(int i = 0; i < eat; i++){
        gameObjectList.push_back(new Enemy(Enemy::Types::EATER, animLib, 200, 40));
    }

    // initialize
    for(vector <GameObject*>::iterator it = gameObjectList.begin();
        it != gameObjectList.end();
        it++){
        (*it)->init();
    }
}

void Game::runLevel(){
    initLevel();
    setBackground("gfx/background2.jpg");
    gameLoop();
}

void Game::runMenu(){
    score = 0;
    level = 1;
    SDL_Surface* jumpBar = NULL;
    SDL_Surface* bottomBar = NULL;
    jumpBar = loadImage("gfx/jumpbar.png", true);
    bottomBar = loadImage("gfx/bottombar.png", false);

    SDL_Rect r;
    r.w = screen->w;
    r.h = 40;
    r.x = 0;
    r.y = 0;

    int jumpBarDY = 10;
    int jumpBarY = 0;

    Game::States state = Game::States::MENU;

    bool quit = false;
    while(quit == false){
        while(r.y < 580){
            int red = rand()%255;
            int green = rand()%255;
            int blue = rand()%255;
            SDL_FillRect(
                screen,
                &r,
                SDL_MapRGB(
                    screen->format,
                    red,
                    green,
                    blue)
            );
            r.y += (int) r.h;
        }
        r.y = 0;


        applySurface(0, jumpBarY, jumpBar, screen);
        jumpBarY += jumpBarDY;
        if(jumpBarY+jumpBar->h > screen->h){
            jumpBarDY = ~jumpBarDY;
        }
        if(jumpBarY < 0){
            jumpBarDY = ~jumpBarDY;
        }

        applySurface(0, (int) (screen->h - bottomBar->h), bottomBar, screen);
        while(SDL_PollEvent(&event)){
            if(event.type == SDL_KEYDOWN){
                switch(event.key.keysym.sym){
                case SDLK_RETURN:
                    state = Game::States::LEVEL;
                    quit = true;
                    break;
                case SDLK_ESCAPE:
                    state = Game::States::QUIT;
                    quit = true;
                    break;
                default:
                    break;
                }

            }
            if(event.type == SDL_QUIT){
                quit = true;
                state = Game::States::QUIT;
            }
        }
        SDL_Flip(screen);

        SDL_Delay(static_cast<int>(1000/FRAMERATE));
    }

    SDL_FreeSurface(jumpBar);
    SDL_FreeSurface(bottomBar);

    if(state == Game::States::LEVEL){
        runState(state);
    }
}


void Game::setBackground(std::string s){
    background = loadImage(s.c_str());
    applySurface(0, 0, background, screen, NULL);
}

void Game::handleError(int e){
    switch(e){
    case SDL_INIT_ERROR:
        printf("Error intializing SDL!\n");
        break;

    case SDL_SCREEN_ERROR:
        printf("Error setting screen mode\n");
        break;

    case SDL_IMAGE_LOAD_ERROR:
        printf("Error loading image resource\n");
        break;

    case UNKNOWN_ERROR:
        printf("Unknown error!\n");
        break;
    }
}

void Game::gameLoop(){
    gameQuitsIn = 0;
    bool quit = false;
    Game::States state;
    string scoreString = "Score: ";

    while(quit == false){

        applySurface(0, 0, background, screen, NULL);
        while(SDL_PollEvent(&event)){
            if(event.type == SDL_QUIT){
                printf("Quit received\n");
                quit = true;
            }
            if(event.type == SDL_KEYDOWN){
                switch(event.key.keysym.sym){
                case SDLK_ESCAPE:
                    quit = true;
                    state = Game::States::MENU;
                    printf("ESCaPE");
                    break;
                case SDLK_RETURN:
                    if(gameQuitsIn != 0 && gameQuitsIn < SDL_GetTicks()){
                        state = Game::States::MENU;
                        quit = true;
                    }
                    break;

                default:
                    break;
                }
            }

        }

        vector <GameObject*>::iterator it;
        // Check update and draw!
        for(vector <GameObject*>::iterator it = gameObjectList.begin();
            it != gameObjectList.end();
            it++){
            (*it)->listen(event, gameObjectList);
            (*it)->update(gameObjectList);
            (*it)->draw(screen);
        }

        if(gameQuitsIn != 0 && gameQuitsIn < SDL_GetTicks()){
            applySurface(0, 130, animLib->get("game-over")->getFrame(), screen, NULL);
        }

        // Run the collision check
        Collision::runCollisionCheck(gameObjectList);
        int enemies = 0;
        // Remove dying objects.
        int numDying = 0;
        bool playerIsAlive = false;
        for(auto it = gameObjectList.begin();
            it != gameObjectList.end();
            it++){
            if((*it)->objectType() == "player"){
                playerIsAlive = true;
            }
            else if((*it)->objectType() == "enemy"){
                enemies++;
            }
            if((*it)->killMe()){
                if((*it)->objectType() == "enemy"){
                    score += static_cast<Enemy*>(*it)->getPoints();
                }
                numDying++;
            }
        }

        if(enemies == 0){
            state = Game::States::LEVEL;
            quit = true;
        }


        if(!playerIsAlive){
            player = NULL;
            if(gameQuitsIn == 0){
                gameQuitsIn = SDL_GetTicks() + 2000;
            }
        }

        // Clean up vector of dying objects

        while(numDying > 0){
            for(vector <GameObject*>::iterator iter = gameObjectList.begin();
                iter != gameObjectList.end();
                iter++){
                if((*iter)->killMe()){
                    deleteObject((*iter));
                    (*iter) = NULL;
                    iter = gameObjectList.erase(iter);
                    numDying--;
                    break;
                }
            }
        }
        scoreString = "Level: " + numberToString(level) + " Score: " + numberToString(score);

        scoreBoard = TTF_RenderText_Solid(font, scoreString.c_str(), textColor);

        applySurface(screen->w-scoreBoard->w - 30, 10, scoreBoard, screen);

        sort(gameObjectList.begin(), gameObjectList.end());

        SDL_Delay(static_cast<int>(1000/FRAMERATE));
        if(SDL_Flip(screen) == -1){
            throw(SDL_SCREEN_ERROR);
        }
    }

    if(state == Game::States::LEVEL){
        level++;
        runState(state);
    }
    else {
        cleanResources();
        if(state == Game::States::MENU){
            player = NULL;
        }
        runState(state);
    }


}

Uint32 TimeLeft(){
    static Uint32 nextTick = 0;
    Uint32 currentTick = SDL_GetTicks();

    if(nextTick <= currentTick){
        nextTick = currentTick + FRAMERATE;
        return 0;
    }
    else {
        return (nextTick-currentTick);
    }
}
