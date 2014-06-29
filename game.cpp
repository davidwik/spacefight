#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "SDL/SDL_mixer.h"
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
#include "sound.h"
#include "soundlibrary.h"


Game::Game(){
    std::string c = getFileContents("dog");
    if( c == ""){
        highscore = 0;
    }
    else {
        highscore = std::stoi(c);
    }
}

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
        break;

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
    }
    delete animLib;
    delete soundLib;
    TTF_CloseFont(font);
    TTF_CloseFont(textFont);
    std::string s;
    s = numberToString(highscore);
    writeToFile(s, "dog");

    gameObjectList.empty();
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
    }
    player = NULL; // Risky??
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

    font = TTF_OpenFont("res/fonts/digifat.ttf", 20);
    textFont = TTF_OpenFont("res/fonts/zig.ttf", 15);


    if(font == NULL || textFont == NULL){
        printf("Failed to open font");
    }

    SDL_WM_SetCaption("Spaaace Fight!", NULL);
    initialized = true;
    animLib = new AnimationLibrary();
    soundLib = new SoundLibrary();
    try {
        soundLib->add(
            "menu-music",
            new Sound(
                "res/audio/menu.ogg",
                Sound::Types::MUSIC,
                4
            )
        );
        soundLib->add(
            "game-music",
            new Sound(
                "res/audio/game.ogg",
                Sound::Types::MUSIC, 20
            )
        );
    }
    catch(int e){
        printf("Error loading music...\n");
        exit(1);
    }
}


void Game::initLevel(){
    gameObjectList.reserve(1000);

    // Re arrange here so Player init isn't called all the time..

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
    for(auto it = gameObjectList.begin();
        it != gameObjectList.end();
        it++){
        (*it)->setSoundLibrary(soundLib);
        (*it)->init();
    }
}

void Game::runLevel(){
    if(!soundLib->isPlayingMusic()){
        soundLib->play("game-music", 1000);
    }
    initLevel();
    setBackground("res/gfx/static/background.jpg");
    if(level > 1){
        waitForNextLevel();
    }
    gameLoop();
}

void Game::waitForNextLevel(){
    bool continue_level = false;

    SDL_Surface *sign = NULL;
    sign = loadImage("res/gfx/static/next.png");
    SDL_Surface *text = NULL;
    string msg = "WELCOME TO LEVEL ";
    msg += numberToString(level);
    SDL_Color tc = {40, 40, 40 };
    Uint8 redCounter = 0;
    while(continue_level == false){

        while(SDL_PollEvent(&event)){
            if(event.type == SDL_KEYDOWN){
                if(event.key.keysym.sym == SDLK_RETURN){
                    continue_level = true;
                }
            }
        }
        SDL_Rect r;
        r.w = 800;
        r.h = sign->h -2;
        r.x = 0;
        r.y = 191;

        Uint8 red = rand()%255;
        Uint8 green = rand()%255;
        Uint8 blue = rand()%255;
        SDL_FillRect(
            screen,
            &r,
            SDL_MapRGB(
                screen->format,
                red,
                green,
                blue
            )
        );
        applySurface(0, 190, sign, screen);
        text = TTF_RenderText_Solid(textFont, msg.c_str(), tc);
        applySurface(73, 190+99, text, screen);
        SDL_FreeSurface(text);
        text = TTF_RenderText_Solid(textFont, "PRESS ENTER TO CONTINUE", SDL_Color { redCounter, 0, 0});
        applySurface(73, 190+99+21, text, screen);
        SDL_FreeSurface(text);
        redCounter += 20;
        if(redCounter > 255){
            redCounter = 0;
        }
        SDL_Flip(screen);
        SDL_Delay(static_cast<int>(1000/FRAMERATE));
    }
    SDL_FreeSurface(sign);



}

void Game::runMenu(){
    soundLib->play("menu-music");

    score = 0;
    level = 1;
    SDL_Surface* jumpBar = NULL;
    SDL_Surface* bottomBar = NULL;
    jumpBar = loadImage("res/gfx/static/jumpbar.png", true);
    bottomBar = loadImage("res/gfx/static/bottombar.png", false);

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
    soundLib->stopMusic();

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

        // Check update and draw!
        for(auto it = gameObjectList.begin();
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
                    iter = gameObjectList.erase(iter);
                    numDying--;
                    break;
                }
            }
        }

        if(score > highscore){
            highscore = score;
        }

        scoreString = "Level: " + numberToString(level) + " Score: " + numberToString(score);
        string highScoreString = "High score: " + numberToString(highscore);
        scoreBoard = TTF_RenderText_Solid(font, scoreString.c_str(), textColor);
        applySurface(screen->w-scoreBoard->w - 30, 10, scoreBoard, screen);
        SDL_FreeSurface(scoreBoard);

        scoreBoard = TTF_RenderText_Solid(font, highScoreString.c_str(), textColor);
        applySurface(screen->w-scoreBoard->w -30, 40, scoreBoard, screen);
        SDL_FreeSurface(scoreBoard);

        sort(gameObjectList.begin(), gameObjectList.end());

        SDL_Delay(static_cast<int>(1000/FRAMERATE));
        if(SDL_Flip(screen) == -1){
            throw(SDL_SCREEN_ERROR);
        }
    }

    SDL_FreeSurface(background);

    if(state == Game::States::LEVEL){
        level++;
        runState(state);
    }
    else {
        soundLib->stopMusic();
        cleanResources();
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
