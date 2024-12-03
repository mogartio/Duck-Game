#include "sound.h"

void SoundPlayer::nonSoundError() {
    if (music == nullptr) {
        throw std::runtime_error("No se ha cargado el audio");
    }
}

SoundPlayer::SoundPlayer(const std::string& path): music(nullptr) {
    music = Mix_LoadWAV(path.c_str());
    if (music == nullptr) {
        std::stringstream error;
        error << "Error al cargar el audio: " << Mix_GetError();
        throw std::runtime_error(error.str());
    }
}

void SoundPlayer::playSound(int loops) {
    nonSoundError();
    int canalgenerado = Mix_PlayChannel(-1, music, loops);
    if (canalgenerado == -1) {
        std::stringstream error;
        error << "Error al reproducir el audio: " << Mix_GetError();
        throw std::runtime_error(error.str());
    }
}

void SoundPlayer::setVolume(int volume) {
    nonSoundError();
    Mix_VolumeChunk(music, volume);  // el volumen va de 0 a 128
}

SoundPlayer::~SoundPlayer() {
    if (music != nullptr) {
        Mix_FreeChunk(music);
        music = nullptr;
    }
}
