#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include "utils.h"
#include "animation.h"
#include "animationlibrary.h"
#include <map>
#include <iostream>
using namespace std;

SDL_Event event;
SDL_Surface* screen;

void init(AnimationLibrary *a){
    Animation* anim = new Animation(60, true);
    anim->addFrame("gfx/1.jpg");
    anim->addFrame("gfx/2.jpg");
    anim->addFrame("gfx/3.jpg");
    anim->addFrame("gfx/4.jpg");
    anim->addFrame("gfx/5.jpg");
    a->add("DEF", anim);
}


void addMore(AnimationLibrary *a){
    Animation* anim = new Animation(60, true);
    anim->addFrame("gfx/shipanim/ship-thrust01.png");
    anim->addFrame("gfx/shipanim/ship-thrust02.png");
    anim->addFrame("gfx/shipanim/ship-thrust03.png");
    anim->addFrame("gfx/shipanim/ship-thrust04.png");
    a->add("SHIP", anim);
}

void loop(AnimationLibrary *a){

   bool quit = false;
   string anim = "DEF";
   SDL_Delay(2000);

   while (quit == false){
       SDL_FillRect(screen, NULL, 0x000000);
       while(SDL_PollEvent(&event)){
            if(event.type == SDL_QUIT){
                printf("QUIT received!");
                quit = true;
            }
            if(event.type == SDL_KEYDOWN){
                switch(event.key.keysym.sym){
                case SDLK_ESCAPE:
                    quit = true;
                    break;

                default:
                    break;
                }
            }
            if(event.type == SDL_KEYUP){
                switch(event.key.keysym.sym){
                case SDLK_LCTRL:
                    anim = "SH2IP";
                    break;
                case SDLK_RCTRL:
                    anim = "DEF";
                    break;
                default:
                    break;
                }
            }
       }

       for(int x = 0; x < 800; x += 100){
           for(int y = 0; y < 600; y += 100){
               try {
                   applySurface(x, y, a->get(anim)->getFrame(), screen, NULL);
               } catch(int e){
                   if(e == ANIMATION_EXCEPTION){
                       printf("Missing animation! Cannot contiue...\n");
                       quit = true;
                   }
               }
           }
       }


       if(SDL_Flip(screen) == -1){
           quit = true;
           printf("ERROR!");
       }
       SDL_Delay(16);
   }
}


int main (int argc, char* argv[]){

    if(SDL_Init(SDL_INIT_EVERYTHING) == -1){
        printf("Test fail\n");
        return 1;
    }

    screen = SDL_SetVideoMode(800, 600, 32, SDL_HWSURFACE | SDL_DOUBLEBUF);
    if(screen == NULL){
        printf("Failed to set screen");
    }

    AnimationLibrary* a = new AnimationLibrary();
    init(a);
    addMore(a);
    loop(a);
    delete a;
    SDL_Quit();


/*



    if(SDL_Flip(screen) == -1){
        printf("Error flipping\n");
        return 1;
    }

    Animation* myAnim = new Animation(8, false);
    myAnim->addFrame("gfx/1.jpg");
    myAnim->addFrame("gfx/2.jpg", 2);
    myAnim->addFrame("gfx/3.jpg", 3);
    myAnim->addFrame("gfx/4.jpg", 4);
    myAnim->addFrame("gfx/5.jpg", 5);

    myAnim->setStatus(Animation::STATUS_PLAY);
    printf("Status: %d", myAnim->getStatus());



    delete myAnim;
    */
    //SDL_Quit();
    return 0;
}
