#include "musichandler.h"

bool MusicHandler::outOfRangeError(uint number) {
    if (number < 0 || number >= list_of_musics.size()) {
        std::cerr << "No existe la musica en la lista" << '\n';
        return false;
    }
    return true;
}


MusicHandler::MusicHandler() {
    for (const auto& path: paths_musics) {
        try {
            list_of_musics.push_back(std::make_unique<MusicPlayer>(path));
        } catch (const std::runtime_error& e) {
            std::cerr << e.what() << '\n';
        }
    }
}

void MusicHandler::playThatMusic(uint number, int loop) {
    if (!outOfRangeError(number)) {
        return;
    }
    try {
        list_of_musics[number]->playMusic(loop);
    } catch (const std::runtime_error& e) {
        std::cerr << e.what() << '\n';
    }
}

void MusicHandler::pauseThatMusic(uint number) {
    if (!outOfRangeError(number)) {
        return;
    }
    try {
        list_of_musics[number]->pauseMusic();
    } catch (const std::runtime_error& e) {
        std::cerr << e.what() << '\n';
    }
}

void MusicHandler::resumeThatMusic(uint number) {
    if (!outOfRangeError(number)) {
        return;
    }
    try {
        list_of_musics[number]->resumeMusic();
    } catch (const std::runtime_error& e) {
        std::cerr << e.what() << '\n';
    }
}

void MusicHandler::stopThatMusic(uint number) {
    if (!outOfRangeError(number)) {
        return;
    }
    try {
        list_of_musics[number]->stopMusic();
    } catch (const std::runtime_error& e) {
        std::cerr << e.what() << '\n';
    }
}

void MusicHandler::setThatVolume(uint number, int volume) {
    if (!outOfRangeError(number)) {
        return;
    }
    try {
        list_of_musics[number]->setVolume(volume);
    } catch (const std::runtime_error& e) {
        std::cerr << e.what() << '\n';
    }
}

MusicHandler::~MusicHandler() {
    if (Mix_QuerySpec(NULL, NULL, NULL)) { // Check if SDL_mixer is initialized
        Mix_HaltChannel(-1);  // Stop all channels
    }
    list_of_musics.clear();  // Free resources
    Mix_CloseAudio();        // Shutdown audio
    Mix_Quit();              // Quit SDL_mixer
}

