#ifndef __SOUNDLIBRARY_H__
#define __SOUNDLIBRARY_H__
#include "sound.h"
#include "errorcodes.h"
#include <unordered_map>
#include <string>

class SoundLibrary {
private:
    std::unordered_map <std::string, Sound*> library;
    std::unordered_map <std::string, int> reservedChannels;

public:
    SoundLibrary();
    ~SoundLibrary();
    void init();
    bool has(std::string key);
    void add(std::string key, Sound* s);
    Sound* get(std::string key);
    void stopChannel(int c);
    /**
     * Saves an integer (id to a channel) together with a tag.
     */
    void addReservedChannel(std::string key, int channel);
    /**
     * Stop playing on the reserved channel and clears the tag
     */
    void stopReservedChannel(std::string key);

    /**
     * Check whether a channel is reserved and return the
     *  channel Id. If not set return -1
     */
    int getReservedChannel(std::string key);

    void play(std::string key, int fadeIn = 0);
    void purge();

    // Controlling the background music.
    void stopMusic();
    bool isPlayingMusic();
    void pauseMusic();
    void setMusicVolume(int vol){

    }
    void resumeMusic();
    void stopAll();
    void muteAll();
    void unMuteAll();
    void remove(std::string key);

};

#endif /* __SOUNDLIBRARY_H__ */
