#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>

class Music {
private:
    Mix_Music* music;
    Mix_Chunk* sound;

public:
    Music();

    void playMusic();
    void playExplosionSound();
    void playShootSound();

    ~Music();
};