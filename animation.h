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
    bool trans;
    Uint32 lastSeen;
    vector <SDL_Surface *> frames;
    vector <SDL_Surface *>::iterator frameIterator;
    unsigned int currentFrame;

public:
    Animation(int framesPerSecond, bool transparent);
    ~Animation();
    void flipHorizontal();
    void flipVertical();

    void addFrame(string imageFile);
    SDL_Surface* getFrame();
};
#endif /* __ANIMATION_H__ */
