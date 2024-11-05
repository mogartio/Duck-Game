#include <string>
#include <vector>
#include <unordered_map>

#include "image.h"
#include "wingState.h"
#include "../../../common/duckState/duckState.h"

enum Color {
    WHITE,
    GREY,
    ORANGE,
    YELLOW
};

class Player {
private:

    SDL_Renderer* rend;
    SDL_RendererFlip flip;
    std::string file;

    std::unordered_map<DuckState, std::vector<Image*>> ducks; 
    std::vector<Image*> wings;

    DuckState state;

    bool weaponON;
    int walk;
    bool flapup;

    Image* duck;
    Image* wing;
    //Weapon weapon;

    void chooseColor(Color color);
    void initializeWingImage(WingState wingState);
    void updateWing(int x, int y);
    void initialiceDuckImages(DuckState state);

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

    ~Player();

};