#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

#include "../../../common/duckState/duckState.h"

#include "image.h"
#include "enums.h"

class Player {
private:
    SDL_Renderer* rend;
    SDL_RendererFlip flip;
    std::string file;

    std::unordered_map<DuckState, std::vector<Image*>> ducks;
    std::vector<Image*> wings;

    DuckState state;

    bool weaponON;
    bool armorOn;
    bool helmetOn;
    int walk;
    bool flapup;
    uint width;
    uint height;
    int x;
    int y;

    Image* duck;
    Image* wing;

    Image* _armor;
    Image* _hombro;
    Image* _helmet;
    Image* _weapon;

    void initializeWingImage(WingState wingState);
    void updateWing(int x, int y);
    void initialiceDuckImages(DuckState state);

public:
    Player(SDL_Renderer* rend, Color color);

    // El tamaño original de los png son del pato 24x24 y del ala 15x15
    void defineSize(int height, int width);

    // Actualizar posicion e imagen
    void update(int x, int y, DuckState newState, Side side);

    // Vacia el inventario
    void dropEverithing();

    // Agarrar un arma
    void weapon(Image* weapon);
    // Devolver el arma
    void dropWeapon();
    // Disparar arma
    void shoot();

    // Agarrar/Droppear armadura
    void armor(Image* armor, Image* hombro);

    // Agarrar/Dropear casco
    void helmet(Image* helmet);

    // Dibujar jugador
    void fill();

    std::pair<int, int> getPosition();

    ~Player();
};
