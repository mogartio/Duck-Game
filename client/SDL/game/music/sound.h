#ifndef SOUND_H
#define SOUND_H
#include <algorithm>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>

class SoundPlayer {
private:
    Mix_Chunk* music;  // Almacena el audio como Mix_Chunk

    void nonSoundError();

public:
    explicit SoundPlayer(const std::string& path);

    void playSound(int loops = 0);  // Reproduce la música en un loop y de predeterminado lo
                                    // reproduce una vez

    void setVolume(int volume);

    ~SoundPlayer();
};
#endif  // !MUSIC_H
