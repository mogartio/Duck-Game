#include "music.h"
#include <stdexcept>

Music::Music() {
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
        throw std::runtime_error("Error al inicializar el audio");
    }

    music = Mix_LoadMUS("assets/game_assets/music/duck_game.mp3");
    if (!music) {
        throw std::runtime_error("Error al cargar la musica");
    }

    sound = Mix_LoadWAV("assets/game_assets/music/explosion.wav");
    if (!sound) {
        throw std::runtime_error("Error al cargar el sonido de explosion");
    }
}

void Music::playMusic() {
    Mix_PlayMusic(music, -1);
}

void Music::playExplosionSound() {
    Mix_PlayChannel(-1, sound, 0);
}

void Music::playShootSound() {
    Mix_PlayChannel(-1, sound, 0);
}

