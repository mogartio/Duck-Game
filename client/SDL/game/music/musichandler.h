#ifndef MUSIC_HANDLER_H
#define MUSIC_HANDLER_H
#include <memory>
#include <string>
#include <vector>

#include "music.h"

class MusicHandler {
private:
    // seleccione estas arbitrareamente pero pueden seleccionar otras

    const std::vector<std::string> paths_musics = {
            "assets/game_assets/music/48.-Pause.wav", 
            "assets/game_assets/sounds/sonidopatiño/cutOffQuack.wav", // Quack
            "assets/game_assets/sounds/equip.wav", // Equipa el arma
            "assets/game_assets/sounds/disarm.wav", // Suelta el arma
            "assets/game_assets/sounds/dacBang.wav", // Cowboy
            "assets/game_assets/sounds/magnum.wav", // Magnum
            "assets/game_assets/sounds/explode.wav", // Explosion
            "assets/game_assets/sounds/jump.wav", // Salto
            "assets/game_assets/sounds/laserRifle.wav", // Rifle laser
            "assets/game_assets/sounds/laserBlast.wav", // Pew Pew Laser
            "assets/game_assets/sounds/pistol.wav", // Duel pistol
            "assets/game_assets/sounds/sniper.wav", // Sniper
            "assets/game_assets/sounds/shotgun.wav", // Shotgun
            }; 
    std::vector<std::unique_ptr<MusicPlayer>> list_of_musics;

    bool outOfRangeError(uint number);

public:
    MusicHandler();

    void playThatMusic(uint number, int loop = 0);  // Reproduce la musica segun el numero de la
                                                    // lista de paths que se le paso al constructor

    void pauseThatMusic(uint number);

    void resumeThatMusic(uint number);

    void stopThatMusic(uint number);

    void setThatVolume(uint number, int volume);

    ~MusicHandler();
};

#endif
