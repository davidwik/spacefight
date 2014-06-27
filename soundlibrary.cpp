#include "soundlibrary.h"

SoundLibrary::SoundLibrary(){
    init();
}


SoundLibrary::~SoundLibrary(){
    printf("Freeing SoundLibrary");
    Mix_Quit();
    purge();
}

bool SoundLibrary::has(std::string key){
    return (library.count(key) > 0) ? true : false;
}

Sound* SoundLibrary::get(std::string key){
    if(!has(key)){
        throw MISSING_INDEX;
    }
    return library[key];
}

void SoundLibrary::add(std::string key, Sound* s){
    if(!has(key)){
        library[key] = s;
    }
}

void SoundLibrary::remove(std::string key){
    if(has(key)){
        std::unordered_map <std::string, Sound*>::iterator it;
        it = library.find(key);
        delete(it->second);
        library.erase(it);
    }
}

void SoundLibrary::play(std::string key, int fadeIn){
    get(key)->play(fadeIn);
}

void SoundLibrary::pauseMusic(){
    if(Mix_PlayingMusic() == 1){
        Mix_PauseMusic();
    }
}

void SoundLibrary::resumeMusic(){
    if(Mix_PausedMusic()){
        Mix_ResumeMusic();
    }
}

void SoundLibrary::stopMusic(){
    if(Mix_PausedMusic() || Mix_PlayingMusic()){
        Mix_HaltMusic();
    }
}


void SoundLibrary::purge(){
    for(auto it = library.begin();
        it != library.end();
        it++){
        delete (it->second);

    }
    library.clear();
}

void SoundLibrary::init(){
    int flags = MIX_INIT_OGG|MIX_INIT_MP3;
    Mix_Init(flags);
    int audio_rate = 44100;
    Uint16 audio_format = AUDIO_S16; /* 16-bit stereo */
    int audio_channels = 2;
    int audio_buffers = 4096;

    if(Mix_OpenAudio(audio_rate, audio_format, audio_channels, audio_buffers)) {
        printf("Unable to open audio!\n");
        exit(1);
    }
}
