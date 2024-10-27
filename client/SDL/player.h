#include <string>
#include <unordered_map>

#include "image.h"
#include "wingState.h"
#include "common/duckState/duckState.h"

class Player {
private:

    SDL_Renderer* rend;
    SDL_RendererFlip flip;
    std::string file;
    std::string action;
    std::string wingType;

    std::unordered_map<DuckState, Image> ducks;
    std::unordered_map<WingState, Image> wings;

    DuckState state;

    bool weaponON;
    bool walk1;
    bool flapup;

    Image* duck;
    Image* wing;
    //Weapon weapon;

    void chooseColor(Color color);
    void checkWingHashmap(WingState wingState);
    void updateWing(int x, int y);

public:
    Player(SDL_Renderer* rend, Color color);

    // El tamaño original de los png son del pato 32x32 y del ala 15x15
    void defineSize(int height, int width);

    // Actualiza la posicion y la imagen
    void update(int x, int y, DuckState newState, Side side);

    // Dibuja el jugador
    void fill();

    // Agarra o suelta un arma
    void weapon(/*tipo de arma*/);

    // Dispara el arma
    void shoot();

};