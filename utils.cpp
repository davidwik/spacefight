#include "utils.h"

std::string getDirectory(){
    char cCurrentPath[FILENAME_MAX];
    if(!GetCurrentDir(cCurrentPath, sizeof(cCurrentPath))){
        throw DIRECTORY_ERROR;
    }
    cCurrentPath[sizeof(cCurrentPath) - 1] = 0;
    std::string path(cCurrentPath);
    path += PATH_SEP;
    return path;
}


std::string getFileContents(std::string filename){
    filename = getDirectory() + filename;
    std::ifstream file(filename, ios::binary);
    string returnData = "";
    string line;
    if(file.is_open()){
        while(getline(file, line)){
            returnData += line;
        }
        file.close();
        return returnData;
    }
    else {
        return "";
    }
}

bool writeToFile(std::string data, std::string filename){
    filename = getDirectory() + filename;
    std::ofstream file(filename, ios::binary);
    if(file.is_open()){
        file << data;
        file.close();
        return true;
    }
    return false;
}



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


void drawRect(SDL_Surface* surface, SDL_Rect rect, Uint32 color){
    drawLine(surface,
             rect.x,
             rect.x+rect.w,
             rect.y,
             rect.y,
             color
    );

    drawLine(surface,
             rect.x+rect.w,
             rect.x+rect.w,
             rect.y,
             rect.y+rect.h,
             color
    );

    drawLine(surface,
             rect.x+rect.w,
             rect.x,
             rect.y+rect.h,
             rect.y+rect.h,
             color
    );

    drawLine(surface,
             rect.x,
             rect.x,
             rect.y,
             rect.y+rect.h,
             color
    );

}

void drawLine(SDL_Surface* surface,
              int x1,
              int x2,
              int y1,
              int y2,
              Uint32 pixel){
    if(SDL_MUSTLOCK(surface)){
        SDL_LockSurface(surface);
    }
    int delta_x = (x2-x1);

    // if x1 == x2, then it does not matter what we set here
    signed char const ix((delta_x > 0) - (delta_x < 0));
    delta_x = std::abs(delta_x) << 1;

    int delta_y(y2 - y1);
    // if y1 == y2, then it does not matter what we set here
    signed char const iy((delta_y > 0) - (delta_y < 0));
    delta_y = std::abs(delta_y) << 1;
    putPixel32(surface, x1, y1, pixel);

    if (delta_x >= delta_y) {
        // error may go below zero
        int error(delta_y - (delta_x >> 1));
        while (x1 != x2) {
            if ((error >= 0) && (error || (ix > 0))){
                error -= delta_x;
                y1 += iy;
            }
            // else do nothing

            error += delta_y;
            x1 += ix;
            putPixel32(surface, x1, y1, pixel);
        }
    }
    else
    {
        // error may go below zero
        int error(delta_x - (delta_y >> 1));

        while (y1 != y2)
        {
            if ((error >= 0) && (error || (iy > 0)))
            {
                error -= delta_y;
                x1 += ix;
            }
            // else do nothing

            error += delta_x;
            y1 += iy;
            putPixel32(surface, x1, y1, pixel);
        }
    }
    if(SDL_MUSTLOCK(surface)){
        SDL_UnlockSurface(surface);
    }
}


SDL_Surface* copySurface(SDL_Surface* image){
    return SDL_ConvertSurface(image,
                              image->format,
                              image->flags);

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
    if(x >= 0 && x < surface->w && y >= 0 && y < surface->h){
        Uint32 *pixels = (Uint32 *)surface->pixels;
        // Set the pixel
        pixels[(y*surface->w)+x] = pixel;
    }
}



SDL_Surface* flipImage(SDL_Surface* surface, int flags){
    SDL_Surface *flipped = NULL;
    flipped = SDL_CreateRGBSurface(
        SDL_HWSURFACE | SDL_SRCALPHA,
        surface->w,
        surface->h,
        surface->format->BitsPerPixel,
        surface->format->Rmask,
        surface->format->Gmask,
        surface->format->Bmask,
        surface->format->Amask
    );

    //If the surface must be locked
    if(SDL_MUSTLOCK(surface)){ //Lock the surface
        SDL_LockSurface( surface );
    }

    for(int x = 0, rx = flipped->w - 1;
        x < flipped->w; x++, rx-- ){ //Go through rows
        for( int y = 0, ry = flipped->h - 1;
             y < flipped->h;
             y++, ry-- ) {
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
    SDL_FreeSurface(surface);
    return flipped;
}

std::string numberToString(int num){
    std::string s = static_cast<std::ostringstream*>( &(std::ostringstream() << num) )->str();
    return s;
}

int floatToInt(float n){
    return static_cast<int>(floor(n + 0.5f));
}

int doubleToInt(double n){
    return static_cast<int>(floor(n+0.5f));
}
