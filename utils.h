#ifndef __UTILS_H__
#define __UTILS_H__
#include <string>
#include <sstream>
const int FLIP_VERTICAL = 1;
const int FLIP_HORIZONTAL = 2;

SDL_Surface* loadImage(std::string filename, bool alpha = true);

void applySurface(
    int x,
    int y,
    SDL_Surface* source,
    SDL_Surface *dest,
    SDL_Rect* clip = NULL
);
SDL_Surface* copySurface(SDL_Surface* image);
Uint32 getPixel32(SDL_Surface* surface, int x, int y);
void putPixel32(SDL_Surface* surface, int x, int y, Uint32 pixel);
std::string numberToString(int num);

SDL_Surface* flipImage(SDL_Surface* surface, int flags);

#endif /* __UTILS_H__ */
