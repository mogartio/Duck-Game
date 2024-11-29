#include "music.h"

#include <sstream>

void MusicPlayer::nonMusicError() {
    if (music == nullptr) {
        throw std::runtime_error("No se ha cargado el audio");
    }
}

void MusicPlayer::nonChannelError() {
    if (canal == -1) {
        throw std::runtime_error("No se ha reproducido el audio");
    }
}

MusicPlayer::MusicPlayer(const std::string& path): music(nullptr), canal(-1) {
    music = Mix_LoadWAV(path.c_str());
    if (music == nullptr) {
        std::stringstream error;
        error << "Error al cargar el audio: " << Mix_GetError();
        throw std::runtime_error(error.str());
    }
}

void MusicPlayer::playMusic(int loops) {
    nonMusicError();
    canal = Mix_PlayChannel(-1, music, loops);
    if (canal == -1) {
        std::stringstream error;
        error << "Error al reproducir el audio: " << Mix_GetError();
        throw std::runtime_error(error.str());
    }
}

void MusicPlayer::pauseMusic() {
    nonMusicError();
    nonChannelError();
    if (Mix_Paused(canal) != 1) {
        Mix_Pause(canal);
    }
}

void MusicPlayer::resumeMusic() {
    nonMusicError();
    nonChannelError();
    if (Mix_Paused(canal) == 1) {
        Mix_Resume(canal);
    }
}

void MusicPlayer::stopMusic() {
    nonMusicError();
    nonChannelError();
    Mix_HaltChannel(canal);
    canal = -1;
}

void MusicPlayer::setVolume(int volume) {
    nonMusicError();
    Mix_VolumeChunk(music, volume);  // el volumen va de 0 a 128
}

MusicPlayer::~MusicPlayer() {
    if (music != nullptr) {
        Mix_FreeChunk(music);
        music = nullptr;
    }
}
