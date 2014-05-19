#include "animation.h"
#include "utils.h"
using namespace std;

Animation::Animation(int framesPerSecond, bool transparent=false){
    fps = framesPerSecond;
    fps_ms = (int) 1000/fps;
    trans = transparent;
    lastSeen = 0;
}

Animation::~Animation() {
    printf("Freeing images in animation");
    for( frameIterator = frames.begin();
         frameIterator != frames.end();
         frameIterator++){
        SDL_FreeSurface(*frameIterator);
    }
}

void Animation::flipHorizontal(){
    for(frameIterator = frames.begin();
        frameIterator != frames.end();
        frameIterator++){
        *frameIterator = flipImage(*frameIterator, FLIP_HORIZONTAL);
    }
}

void Animation::flipVertical(){
    for(frameIterator = frames.begin();
        frameIterator != frames.end();
        frameIterator++){
        *frameIterator = flipImage(*frameIterator, FLIP_VERTICAL);
    }
}

SDL_Surface* Animation::getFrame(){
    Uint32 currTick = SDL_GetTicks();
    if((currTick-lastSeen) > fps_ms){
        currentFrame++;
        lastSeen = currTick;
    }

    if(currentFrame >= frames.size()){
        currentFrame = 0;
    }
    return frames.at(currentFrame);
}

void Animation::addFrame(string imageFile){
    frames.push_back(loadImage(imageFile, trans));
    printf("%s loaded!\n", imageFile.c_str());
}
