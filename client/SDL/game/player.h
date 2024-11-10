#include <string>
#include <vector>
#include <unordered_map>

#include "image.h"
#include "enums.h"
#include "../../../common/duckState/duckState.h"

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

    // Agarrar un arma
    void weapon(Image* weapon);
    // Devolver el arma
    Image* dropWeapon();

    // Agarrar armadura
    void armor(Image* armor, Image* hombro);
    // Devolver armadura
    Image* dropArmor();

    // Agarrar casco
    void helmet(Image* helmet);
    // Devolver casco
    Image* dropHelmet();

    // Disparar arma
    void shoot();

    // Dibujar jugador
    void fill();


    ~Player();

};