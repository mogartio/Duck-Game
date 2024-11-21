#include "music.h"
#include <iostream>

Music* activeMusic = nullptr;

void Music::onMusicFinished() {
    if (!activeMusic) return;

    currentSongIndex++;
    if (currentSongIndex >= activeMusic->songs.size()) {
        std::cout << "Todas las canciones han terminado." << std::endl;
        return;
    }

    Mix_Music* nextMusic = activeMusic->songs[currentSongIndex];
    if (Mix_PlayMusic(nextMusic, 1) == -1) {
        std::cerr << "Error al reproducir la canción: " << Mix_GetError() << std::endl;
    } else {
        std::cout << "Reproduciendo siguiente canción..." << std::endl;
    }
}

void globalOnMusicFinished() {
    if (activeMusic) {
        activeMusic->onMusicFinished();
    }
}

Music::Music() : music(nullptr), sound(nullptr) {
    activeMusic = this; 
    Mix_HookMusicFinished(globalOnMusicFinished);
}

void Music::playMusic() {
    if (songs.empty()) {
        std::cerr << "No hay canciones cargadas en el vector." << std::endl;
        return;
    }

    currentSongIndex = 0;
    music = songs[currentSongIndex];

    if (Mix_PlayMusic(music, 1) == -1) {
        std::cerr << "Error al reproducir la canción: " << Mix_GetError() << std::endl;
    } else {
        std::cout << "Reproduciendo primera canción..." << std::endl;
    }
}

void Music::playIntenseMusic() {
    if (!songs[5]) {
        std::cerr << "Música intensa no válida. playIntenseMusic" << std::endl;
        return;
    }

    // Pausa la música actual
    if (Mix_PlayingMusic()) {
        Mix_PauseMusic();
    }

    // Reproduce la música intensa (Boss music)
    if (Mix_PlayMusic(songs[5], 1) == -1) {
        std::cerr << "Error al reproducir la música intensa: " << Mix_GetError() << std::endl;
    }
}

void Music::playExplosionSound() {
    if (!sound) {
        std::cerr << "Efecto de sonido no cargado." << std::endl;
        return;
    }

    if (Mix_PlayChannel(-1, sound, 0) == -1) {
        std::cerr << "Error al reproducir efecto de sonido: " << Mix_GetError() << std::endl;
    } else {
        std::cout << "Reproduciendo sonido de explosión..." << std::endl;
    }
}

void Music::playShootSound() {
    if (!sound) {
        std::cerr << "Efecto de sonido no cargado." << std::endl;
        return;
    }

    if (Mix_PlayChannel(-1, sound, 0) == -1) {
        std::cerr << "Error al reproducir efecto de sonido: " << Mix_GetError() << std::endl;
    } else {
        std::cout << "Reproduciendo sonido de disparo..." << std::endl;
    }
}

Music::~Music() {
    for (Mix_Music* song : songs) {
        Mix_FreeMusic(song);
    }
    Mix_FreeChunk(sound);
    Mix_CloseAudio();
    std::cout << "Recursos de música liberados." << std::endl;
}
