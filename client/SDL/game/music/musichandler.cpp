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

    for (const auto& path: paths_sounds) {
        try {
            list_of_sounds.push_back(std::make_unique<SoundPlayer>(path));
            list_of_sounds.back()->setVolume(7);
        } catch (const std::runtime_error& e) {
            std::cerr << e.what() << '\n';
        }
    }
}

void MusicHandler::playThatMusic(Music number, int loop) {
    int numberint = static_cast<int>(number);
    if (!outOfRangeError(numberint)) {
        return;
    }
    try {
        list_of_musics[numberint]->playMusic(loop);
    } catch (const std::runtime_error& e) {
        std::cerr << e.what() << '\n';
    }
}

void MusicHandler::pauseThatMusic(Music number) {
    int numberint = static_cast<int>(number);
    if (!outOfRangeError(numberint)) {
        return;
    }
    try {
        list_of_musics[numberint]->pauseMusic();
    } catch (const std::runtime_error& e) {
        std::cerr << e.what() << '\n';
    }
}

void MusicHandler::resumeThatMusic(Music number) {
    int numberint = static_cast<int>(number);
    if (!outOfRangeError(numberint)) {
        return;
    }
    try {
        list_of_musics[numberint]->resumeMusic();
    } catch (const std::runtime_error& e) {
        std::cerr << e.what() << '\n';
    }
}

void MusicHandler::stopThatMusic(Music number) {
    int numberint = static_cast<int>(number);
    if (!outOfRangeError(numberint)) {
        return;
    }
    try {
        list_of_musics[numberint]->stopMusic();
    } catch (const std::runtime_error& e) {
        std::cerr << e.what() << '\n';
    }
}

void MusicHandler::setThatVolume(Music number, int volume) {
    int numberint = static_cast<int>(number);
    if (!outOfRangeError(numberint)) {
        return;
    }
    try {
        list_of_musics[numberint]->setVolume(volume);
    } catch (const std::runtime_error& e) {
        std::cerr << e.what() << '\n';
    }
}

void MusicHandler::playThatSound(Sound number) {
    int numberint = static_cast<int>(number);
    if (numberint < 0 || static_cast<int>(list_of_sounds.size()) <= numberint) {
        std::cerr << "No existe el sonido en la lista" << '\n';
        return;
    }
    try {
        list_of_sounds[numberint]->playSound();
    } catch (const std::runtime_error& e) {
        std::cerr << e.what() << '\n';
    }
}

void MusicHandler::setSoundVolume(Sound number, int volume) {
    int numberint = static_cast<int>(number);
    if (numberint < 0 || static_cast<int>(list_of_sounds.size()) <= numberint) {
        std::cerr << "No existe el sonido en la lista" << '\n';
        return;
    }
    try {
        list_of_sounds[numberint]->setVolume(volume);
    } catch (const std::runtime_error& e) {
        std::cerr << e.what() << '\n';
    }
}

MusicHandler::Sound MusicHandler::getSound(ProjectilesId::ProjectileId projectileId) {
    switch (projectileId) {
        case ProjectilesId::ProjectileId::AK_47:
            return Sound::PISTOL;
        case ProjectilesId::ProjectileId::DUEL_PISTOL:
            return Sound::PISTOL;
        case ProjectilesId::ProjectileId::COWBOY_PISTOL:
            return Sound::PISTOL;
        case ProjectilesId::ProjectileId::MAGNUM:
            return Sound::MAGNUM;
        case ProjectilesId::ProjectileId::SNIPER:
            return Sound::SNIPER;
        case ProjectilesId::ProjectileId::SHOTGUN:
            return Sound::SHOTGUN;
        case ProjectilesId::ProjectileId::PEW_PEW_LASER:
            return Sound::LASERBLAST;
        case ProjectilesId::ProjectileId::LASER_RIFLE:
            return Sound::LASERRIFLE;
        case ProjectilesId::ProjectileId::BANANA:
            return Sound::DACBANG;
        default:
            return Sound::QUACK;
    }
}

MusicHandler::~MusicHandler() {
    if (Mix_QuerySpec(NULL, NULL, NULL)) {  // Check if SDL_mixer is initialized
        Mix_HaltChannel(-1);                // Stop all channels
    }
    list_of_musics.clear();  // Free resources
    Mix_CloseAudio();        // Shutdown audio
    Mix_Quit();              // Quit SDL_mixer
}
