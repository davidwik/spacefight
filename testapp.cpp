#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <vector>
#include <map>
#include <string>
#include "utils.h"


using namespace std;

class Animation {
    vector <SDL_Surface *> imageList;
    vector <SDL_Surface *>::iterator listIterator;
    int fps;
    bool trans;
public:
    void loadImageIntoList(string imageURL);
    void show(unsigned int index);
    void setTransparent(bool t){ trans = t;}
    SDL_Surface* getFrame(unsigned int i);
    Animation(int framesPerSecond, bool transparent);
    ~Animation();
};



Animation::Animation(int framesPerSecond, bool transparent = false){
    fps = framesPerSecond;
    trans = transparent;

}

SDL_Surface* Animation::getFrame(unsigned int i){
    if((unsigned) i >= imageList.size()){
        printf("\nOut of index showing last image..\n");
        return imageList.at(imageList.size()-1);
    }
    else {
        printf("\nShowing image %d of %lu", i+1, imageList.size());
        return imageList.at(i);
    }
}

Animation::~Animation(){
    // Free resources??
    printf("Killing all images!\n");
    for(listIterator = imageList.begin();
        listIterator != imageList.end();
        listIterator++){
        SDL_FreeSurface(*listIterator);
    }
}

map <string, Animation*> animationList;
map <string, Animation*>::iterator mapIter;

void Animation::loadImageIntoList(string imageURL){
    printf("Loading: %s", imageURL.c_str());
    imageList.push_back(loadImage(imageURL, trans));
}

int main (int argc, char* argv[]){
    if(SDL_Init(SDL_INIT_EVERYTHING) == -1){
        printf("Test fail\n");
        return 1;
    }
    SDL_Surface* screen;
    screen = SDL_SetVideoMode(800, 600, 32, SDL_HWSURFACE);
    if(!screen){
        printf("Screen fail\n");
        return 1;
    }

    animationList["WALK"] = new Animation(4);
    animationList["WALK"]->loadImageIntoList("gfx/1.jpg");
    animationList["WALK"]->loadImageIntoList("gfx/2.jpg");
    animationList["WALK"]->loadImageIntoList("gfx/3.jpg");
    animationList["WALK"]->loadImageIntoList("gfx/4.jpg");
    animationList["WALK"]->loadImageIntoList("gfx/5.jpg");

    animationList["RUN"] = new Animation(4);
    animationList["RUN"]->loadImageIntoList("gfx/1.jpg");
    animationList["RUN"]->loadImageIntoList("gfx/2.jpg");
    animationList["RUN"]->loadImageIntoList("gfx/3.jpg");
    animationList["RUN"]->loadImageIntoList("gfx/4.jpg");
    animationList["RUN"]->loadImageIntoList("gfx/5.jpg");



    applySurface(0, 10, animationList["WALK"]->getFrame(0), screen, NULL);
    applySurface(100, 10, animationList["WALK"]->getFrame(1), screen, NULL);
    applySurface(200, 10, animationList["WALK"]->getFrame(2), screen, NULL);
    applySurface(300, 10, animationList["WALK"]->getFrame(3), screen, NULL);
    applySurface(400, 10, animationList["WALK"]->getFrame(4), screen, NULL);

    applySurface(0, 120, animationList["RUN"]->getFrame(0), screen, NULL);
    applySurface(100, 120, animationList["RUN"]->getFrame(1), screen, NULL);
    applySurface(200, 120, animationList["RUN"]->getFrame(2), screen, NULL);
    applySurface(300, 120, animationList["RUN"]->getFrame(3), screen, NULL);
    applySurface(400, 120, animationList["RUN"]->getFrame(4), screen, NULL);


    if(SDL_Flip(screen) == -1){
        printf("Error flipping\n");
        return 1;
    }



    SDL_Delay(3000);

    for(std::map<string, Animation*>::iterator mapIter=animationList.begin();
        mapIter!=animationList.end();
        mapIter++){
        delete mapIter->second;
    }

    //delete animationList["WALK"];
    //delete animationList["RUN"];

    SDL_Quit();
    return 0;
}
