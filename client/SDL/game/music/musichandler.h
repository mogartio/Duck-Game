#ifndef MUSIC_HANDLER_H
#define MUSIC_HANDLER_H
#include <memory>
#include <string>
#include <vector>

#include "../../../../common/messages/generic_msg.h"

#include "music.h"
#include "sound.h"

class MusicHandler {
private:
    // seleccione estas arbitrareamente pero pueden seleccionar otras

    const std::vector<std::string> paths_musics = {
            "assets/game_assets/music/48.-Pause.wav",
    };

    std::vector<std::unique_ptr<MusicPlayer>> list_of_musics;

    const std::vector<std::string> paths_sounds = {
            "assets/game_assets/sounds/sonidopatiño/cutOffQuack.wav",  // Quack
            "assets/game_assets/sounds/equip.wav",                     // Equipa el arma
            "assets/game_assets/sounds/disarm.wav",                    // Suelta el arma
            "assets/game_assets/sounds/dacBang.wav",                   // Cowboy
            "assets/game_assets/sounds/magnum.wav",                    // Magnum
            "assets/game_assets/sounds/explode.wav",                   // Explosion
            "assets/game_assets/sounds/jump.wav",                      // Salto
            "assets/game_assets/sounds/laserRifle.wav",                // Rifle laser
            "assets/game_assets/sounds/laserBlast.wav",                // Pew Pew Laser
            "assets/game_assets/sounds/pistol.wav",                    // Duel pistol
            "assets/game_assets/sounds/sniper.wav",                    // Sniper
            "assets/game_assets/sounds/shotgun.wav",                   // Shotgun
    };

    std::vector<std::unique_ptr<SoundPlayer>> list_of_sounds;

    bool outOfRangeError(uint number);

public:
    enum class Music : int {
        PAUSE = 0,
    };

    enum class Sound : int {
        QUACK = 0,
        EQUIP,
        DISARM,
        DACBANG,
        MAGNUM,
        EXPLODE,
        JUMP,
        LASERRIFLE,
        LASERBLAST,
        PISTOL,
        SNIPER,
        SHOTGUN,
    };

    MusicHandler();

    void playThatMusic(Music number, int loop = 0);  // Reproduce la musica segun el numero de la
                                                     // lista de paths que se le paso al constructor

    void pauseThatMusic(Music number);

    void resumeThatMusic(Music number);

    void stopThatMusic(Music number);

    void setThatVolume(Music number, int volume);

    void playThatSound(Sound number);  // Reproduce el sonido segun el numero de la lista de paths
                                       // que se le paso al constructor

    void setSoundVolume(Sound number, int volume);

    Sound getSound(ProjectilesId::ProjectileId projectileId);

    ~MusicHandler();
};

#endif
