#include "animation.h"
#include "utils.h"
using namespace std;

Animation::Animation(int framesPerSecond, bool transparent=false){
    fps = framesPerSecond;
    fps_ms = (int) 1000/fps;
    trans = transparent;
    lastSeen = 0;
    status = Animation::STATUS_PLAY;
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

void Animation::setStatus(short st){
    switch(st){
    case STATUS_STOP:
        status = STATUS_STOP;
        break;
    case STATUS_PLAY:
        status = STATUS_PLAY;
        break;
    case STATUS_PAUSE:
        status = STATUS_PAUSE;
        break;
     default:
         ;
     }
 }

short Animation::getStatus(){
    return status;
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
    // IF STATUS IS STOPPED
    if(status == Animation::STATUS_STOP){
        return frames.at(0);
    }
    // PAUSED
    else if(status == Animation::STATUS_PAUSE){
        lastSeen = currTick;
        if(currentFrame >= frames.size()){
            currentFrame = 0;
        }
        return frames.at(currentFrame);
    }

    int unsigned currIndex = currentFrame;
    if(currIndex >= frame_multiplier.size()){
        currIndex = 0;
    }
    Uint32 fps_for_frame = (Uint32) fps_ms*(frame_multiplier.at(currIndex));
    if((currTick-lastSeen) > fps_for_frame){
        currentFrame++;
        lastSeen = currTick;
    }

    if(currentFrame >= frames.size()){
        currentFrame = 0;
    }
    return frames.at(currentFrame);
}

void Animation::addFrame(string imageFile, float multiplier){
    frames.push_back(loadImage(imageFile, trans));
    frame_multiplier.push_back(multiplier);
    printf("%s loaded!\n", imageFile.c_str());
}
