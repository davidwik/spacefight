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


/**
 * Get pixel value in Uint32
 *
 */
Uint32 getPixel32(SDL_Surface* surface, int x, int y){
    // Convert pixels to Uint32
    Uint32 *pixels = (Uint32 *)surface->pixels;
    // return the requested pixel
    return pixels[(y*surface->w) + x];
}

/**
 * Put Uint32 as pixel value on pixel
 */
void putPixel32(SDL_Surface* surface, int x, int y, Uint32 pixel){
    // convert the pixels to Uint32
    Uint32 *pixels = (Uint32 *)surface->pixels;
    // Set the pixel
    pixels[(y*surface->w)+x] = pixel;
}



SDL_Surface* flipImage(SDL_Surface* surface, int flags){
    SDL_Surface *flipped = NULL;
    //If the image is color keyed
    if( surface->flags & SDL_SRCCOLORKEY ) {
        flipped = SDL_CreateRGBSurface(
            SDL_SWSURFACE,
            surface->w,
            surface->h,
            surface->format->BitsPerPixel,
            surface->format->Rmask,
            surface->format->Gmask,
            surface->format->Bmask, 0 );

    } //Otherwise
    else {
        flipped = SDL_CreateRGBSurface(
            SDL_SWSURFACE,
            surface->w,
            surface->h,
            surface->format->BitsPerPixel,
            surface->format->Rmask,
            surface->format->Gmask,
            surface->format->Bmask,
            surface->format->Amask );
    }

    //If the surface must be locked
    if(SDL_MUSTLOCK(surface)){ //Lock the surface
        SDL_LockSurface( surface );
    }

    for(int x = 0, rx = flipped->w - 1;
        x < flipped->w; x++, rx-- ){ //Go through rows
        for( int y = 0, ry = flipped->h - 1; y < flipped->h; y++, ry-- ) {
            Uint32 pixel = getPixel32( surface, x, y );
            if((flags & FLIP_VERTICAL) && (flags & FLIP_HORIZONTAL)) {
                putPixel32(flipped, rx, ry, pixel);
            }
            else if( flags & FLIP_HORIZONTAL ) {
                putPixel32( flipped, rx, y, pixel);
            }
            else if( flags & FLIP_VERTICAL ) {
                putPixel32( flipped, x, ry, pixel);
            }
        }
    }

    if(SDL_MUSTLOCK(surface)){
        SDL_UnlockSurface(surface);
    }

    // Copy color key
    if(surface->flags && SDL_SRCCOLORKEY){
        SDL_SetColorKey(flipped, SDL_RLEACCEL | SDL_SRCCOLORKEY, surface->format->colorkey);
    }
    return flipped;

}
