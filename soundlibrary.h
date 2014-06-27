#ifndef __SOUNDLIBRARY_H__
#define __SOUNDLIBRARY_H__
#include "sound.h"
#include "errorcodes.h"
#include <unordered_map>
#include <string>

class SoundLibrary {
private:
    std::unordered_map <std::string, Sound*> library;

public:
    SoundLibrary();
    ~SoundLibrary();
    void init();
    bool has(std::string key);
    void add(std::string key, Sound* s);
    Sound* get(std::string key);
    void play(std::string key, int fadeIn = 0);
    void purge();

    // Controlling the background music.
    void stopMusic();
    void pauseMusic();
    void resumeMusic();

    void stopAll();
    void muteAll();
    void unMuteAll();
    void remove(std::string key);

};

#endif /* __SOUNDLIBRARY_H__ */
