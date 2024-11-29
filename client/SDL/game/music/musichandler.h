#include <memory>
#include <string>
#include <vector>

#include "music.h"

class MusicHandler {
private:
    // seleccione estas arbitrareamente pero pueden seleccionar otras
    const std::vector<std::string> paths_musics = {
            "assets/game_assets/music/arbuckle.wav", "assets/game_assets/music/arcade.wav",
            "assets/game_assets/music/backwen.wav",
            "assets/game_assets/music/castil.wav"};  // Lista de paths de las musicas

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
