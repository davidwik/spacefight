#include "animation.h"
#include "utils.h"
using namespace std;

Animation::Animation(int framesPerSecond, bool transparent, unsigned int reserve){
    fps = framesPerSecond;
    fps_ms = (int) 1000/fps;
    trans = transparent;
    lastSeen = 0;
    status = Animation::STATUS_PLAY;
    vFlip = false;
    hFlip = false;
    frames.reserve(20);
}

Animation::~Animation() {
    for( frameIterator = frames.begin();
         frameIterator != frames.end();
         frameIterator++){
        SDL_FreeSurface(*frameIterator);
    }
}


Animation* Animation::clone(void){
    Animation* newAnim = new Animation(fps, trans);
    newAnim->lastSeen = 0;
    newAnim->vFlip = vFlip;
    newAnim->hFlip = hFlip;
    newAnim->currentFrame = 0;

    // Copy and create new frames for the animation
    for(vector <SDL_Surface* >::iterator it = frames.begin();
        it != frames.end();
        it++){
        SDL_Surface* tmp = NULL;
        tmp = copySurface(*it);
        newAnim->frames.push_back(tmp);

    }

    // Also copy the frame timing vector
    for(vector <float>::iterator it = frame_multiplier.begin();
        it != frame_multiplier.end();
        it++){
        newAnim->frame_multiplier.push_back(*it);
    }

    return newAnim;
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

void Animation::flipHorizontal(){
    hFlip = (hFlip == false) ? true : false;
    for(frameIterator = frames.begin();
        frameIterator != frames.end();
        frameIterator++){
        SDL_Surface* tmp = NULL;
        tmp = copySurface(*frameIterator);
        SDL_FreeSurface(*frameIterator);
        *frameIterator = flipImage(copySurface(tmp), FLIP_HORIZONTAL);
        SDL_FreeSurface(tmp);

    }
}

unsigned long Animation::numberOfFrames(){
    return frames.size();
}

void Animation::flipVertical(){
    vFlip = (vFlip == false) ? true : false;
    for(frameIterator = frames.begin();
         frameIterator != frames.end();
         frameIterator++){
        SDL_Surface* tmp = NULL;
        tmp = copySurface(*frameIterator);
        SDL_FreeSurface(*frameIterator);
        *frameIterator = flipImage(copySurface(tmp), FLIP_VERTICAL);
        SDL_FreeSurface(tmp);
    }
}

SDL_Surface* Animation::getFrame(){
    // if lastseen is null get the time now, so
    // the first frame can be shown
    if(!lastSeen){
        lastSeen = SDL_GetTicks();
    }
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
}

bool Animation::isFlippedV(){
    return vFlip;
}

bool Animation::isFlippedH(){
    return hFlip;
}

void Animation::reset(){
    if(hFlip){
        flipHorizontal();
    }
    if(vFlip){
        flipVertical();
    }
    currentFrame = 0;
    lastSeen = 0;
}
