#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include <vector>

class Music {
private:
    Mix_Music* music;
    std::vector<Mix_Music*> songs;
    int currentSongIndex;
    Mix_Chunk* sound;

public:
    Music();

    void playMusic();
    void playIntenseMusic();
    void playFinishedMusic();
    void playExplosionSound();
    void playShootSound();
    void onMusicFinished();

    ~Music();
};