#include "sound.h"
Sound::Sound(std::string file, Sound::Types t, int volume){
    type = (int) t;
    v = volume;
    loaded = loadFile(file);
    if(!loaded){
        throw(SDL_FILE_LOAD_ERROR);
    }
}

bool Sound::loadFile(std::string file){
    switch((Sound::Types) type){
    case Sound::Types::MUSIC:
        music = Mix_LoadMUS(file.c_str());
        return (music == NULL ) ? false : true;
        break;
    case Sound::Types::EFFECT:
        effect = Mix_LoadWAV(file.c_str());
        if(effect == NULL){
            printf("SOUND FAILED...\n");
        }
        return (effect == NULL) ? false : true;
        break;
    default:
        return false;
        break;
    }
}


Sound::~Sound(){
    switch((Sound::Types) type){
    case Sound::Types::MUSIC:
        if(music != NULL){
            Mix_FreeMusic(music);
        }
        break;

    case Sound::Types::EFFECT:
        if(effect != NULL){
            Mix_FreeChunk(effect);
        }
        break;

    default:
        break;
    }
    music = NULL;
    effect = NULL;
}

void Sound::play(){
    if(!loaded){
        printf("Sound not loaded!");
    }
    else {
        if((Sound::Types) type == Sound::Types::EFFECT){
            int ch = Mix_PlayChannel(-1, effect, 10);
            Mix_Volume(ch, 30);
        }
    }
}

bool Sound::isPlaying(){
    return false;
}
