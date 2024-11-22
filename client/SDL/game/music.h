#include <iostream>
#include <string>

#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>

class MusicPlayer {
private:
    Mix_Chunk* music;  // Almacena el audio como Mix_Chunk
    int canal;         // Canal de audio

    void nonMusicError();

    void nonChannelError();

public:
    explicit MusicPlayer(const std::string& path);

    void playMusic(int loops = 0);  // Reproduce la música en un loop y de predeterminado lo
                                    // reproduce una vez

    void pauseMusic();

    void resumeMusic();

    void stopMusic();

    void setVolume(int volume);

    ~MusicPlayer();
};
