#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include <string>
#include "utils.h"

SDL_Surface* loadImage(std::string filename, bool useAlpha){
    SDL_Surface* loadedImage = NULL;
    SDL_Surface* optimizedImage = NULL;

    loadedImage = IMG_Load(filename.c_str());
    if(loadedImage != NULL){
        if(useAlpha == true){
            optimizedImage = SDL_DisplayFormatAlpha(loadedImage);
        }
        else {
            optimizedImage = SDL_DisplayFormat(loadedImage);
        }
        SDL_FreeSurface(loadedImage);
    }
    return optimizedImage;
}

void applySurface(int x,
                  int y,
                  SDL_Surface* source,
                  SDL_Surface* dest,
                  SDL_Rect* clip){
    SDL_Rect offset;
    offset.x = x;
    offset.y = y;
    SDL_BlitSurface(source, clip, dest, &offset);
}
