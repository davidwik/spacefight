#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <vector>
#include <string>
#include "utils.h"


using namespace std;

class Animation {
    vector <SDL_Surface *> imageList;
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
    printf("Deleted");
}

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



   Animation anim = Animation(2, false);
   anim.loadImageIntoList("gfx/1.jpg");
   anim.loadImageIntoList("gfx/2.jpg");
   anim.loadImageIntoList("gfx/3.jpg");
   anim.loadImageIntoList("gfx/4.jpg");
   anim.loadImageIntoList("gfx/5.jpg");

   applySurface(0, 10, anim.getFrame(0), screen, NULL);
   applySurface(100, 10, anim.getFrame(1), screen, NULL);
   applySurface(200, 10, anim.getFrame(2), screen, NULL);
   applySurface(300, 10, anim.getFrame(3), screen, NULL);
   applySurface(400, 10, anim.getFrame(4), screen, NULL);
   applySurface(500, 10, anim.getFrame(5), screen, NULL);
   if(SDL_Flip(screen) == -1){
       printf("Error flipping\n");
       return 1;
   }

   SDL_Delay(3000);
   SDL_Quit();
   return 0;
}
