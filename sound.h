#ifndef __SOUND_H__
#define __SOUND_H__
#include "SDL/SDL.h"
#include "SDL/SDL_mixer.h"
#include "errorcodes.h"
#include "utils.h"
#include <string>
class Sound {
private:
    Mix_Chunk* effect = NULL;
    Mix_Music* music = NULL;
    int type;
    int v = 0;
    bool loaded = false;

protected:
    bool loadFile(std::string file);

public:
    enum class Types { MUSIC, EFFECT };
    Sound(std::string file, Sound::Types t, int volume);
    ~Sound();
    bool isPlaying();
    int play(int fade = 0);
    int playLoopedEffect();

};

#endif /* __SOUND_H__ */
