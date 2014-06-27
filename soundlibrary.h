#ifndef __SOUNDLIBRARY_H__
#define __SOUNDLIBRARY_H__
#include "sound.h"
#include <unordered_map>
#include <string>

class SoundLibrary {
private:
    std::unordered_map <std::string, Sound*> library;


public:
    SoundLibrary();
    ~SoundLibrary();
    void init();
    bool has(string key);
    void add(string key, Sound* s);
    Sound* get(string key);
    void purge();
    void stopAll();
    void muteAll();
    void unMuteAll();

    void remove(string key);

};


#endif /* __SOUNDLIBRARY_H__ */
