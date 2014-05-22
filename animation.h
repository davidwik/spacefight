#ifndef __ANIMATION_H__
#define __ANIMATION_H__
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <vector>
#include <string>
using namespace std;

class Animation {

protected:
    unsigned int fps;
    unsigned int fps_ms;
    short status;
    bool trans;
    Uint32 lastSeen;
    bool vFlip;
    bool hFlip;
    vector <SDL_Surface *> frames;
    vector <float> frame_multiplier;
    vector <SDL_Surface *>::iterator frameIterator;
    unsigned int currentFrame;

public:
    static const short STATUS_STOP = 0;
    static const short STATUS_PLAY = 1;
    static const short STATUS_PAUSE = 2;

    Animation(int framesPerSecond = 5, bool transparent = true, unsigned int reserve = 20);
    ~Animation();
    Animation* clone();
    void flipHorizontal();
    void flipVertical();
    void reset();
    void setStatus(short status);
    short getStatus();
    bool isFlippedV();
    bool isFlippedH();
    unsigned long numberOfFrames();
    void addFrame(string imageFile, float multiplier=1.0);
    SDL_Surface* getFrame();
};
#endif /* __ANIMATION_H__ */
