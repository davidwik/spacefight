#ifndef __UTILS_H__
#define __UTILS_H__
#include <string>
#include <sstream>
#include <cstdlib>
#include <cmath>
#include <cstdio>
#include <iostream>
#include <fstream>
#include "constants.h"
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "errorcodes.h"

#ifdef WINDOWS
   #include <direct.h>
   #define PATH_SEP '\''
   #define GetCurrentDir _getcwd
#else
   #include <unistd.h>
   #define PATH_SEP '/'
   #define GetCurrentDir getcwd
#endif

#include <physfs.h>
#include "physfsrwops.h"


using namespace std;

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

std::string getDirectory();

std::string getFileContents(std::string filename);
bool writeToFile(std::string data, std::string filename);

void drawRect(SDL_Surface* surface, SDL_Rect rect, Uint32 color);
void drawLine(SDL_Surface*, int x1, int x2, int y1, int y2, Uint32 color);
int floatToInt(float n);
int doubleToInt(double n);
SDL_Surface* flipImage(SDL_Surface* surface, int flags);

#endif /* __UTILS_H__ */
