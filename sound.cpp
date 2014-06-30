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
    SDL_RWops* rw = getResource(file);

    switch((Sound::Types) type){
    case Sound::Types::MUSIC:
        music = Mix_LoadMUS_RW(rw);
        //L_FreeRW(rw);
        return (music == NULL ) ? false : true;
        break;
    case Sound::Types::EFFECT:


        //effect = Mix_LoadWAV(file.c_str());
        effect = Mix_LoadWAV_RW(rw, 1);
        if(!effect){
            printf("Failed loading effect from: %s\n", file.c_str());
        }

        Mix_VolumeChunk(effect, v);
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
    if(music != NULL){
        Mix_FreeMusic(music);
        printf("Free'd Music\n");
    }
    if(effect != NULL){
        Mix_FreeChunk(effect);
        printf("Free'd effect\n");
    }

}

void Sound::play(int fade){
    if(!loaded){
        printf("Sound not loaded!");
    }
    else {
        if((Sound::Types) type == Sound::Types::EFFECT){
            int ch = Mix_PlayChannel(-1, effect, 0);

            if(ch == -1){
                throw AUDIO_PLAYBACK_ERROR;
            }
        }
        else if((Sound::Types) type == Sound::Types::MUSIC){
            int res = 0;
            Mix_VolumeMusic(v);
            if(fade > 0){
                res = Mix_FadeInMusic(music, -1, fade);
            }
            else {
                res = Mix_PlayMusic(music, -1);
            }
            if(res == -1){
                printf("Failed to open playback..\n");
                throw AUDIO_PLAYBACK_ERROR;
            }
            printf("Playing Music with volume: %d\n", v);

        }
    }
}

bool Sound::isPlaying(){
    return false;
}
