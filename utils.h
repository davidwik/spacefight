#ifndef __UTILS_H__
#define __UTILS_H__

#include <string>

SDL_Surface* loadImage(std::string filename, bool alpha = true);

void applySurface(
    int x,
    int y,
    SDL_Surface* source,
    SDL_Surface *dest,
    SDL_Rect* clip = NULL
);

#endif /* __UTILS_H__ */
