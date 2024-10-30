#include "player.h"
#include <vector>

#define OFFSETX 10

void Player::chooseColor(Color color) {
    switch (color) {
        case WHITE:
            file += "white/";
            break;
        case GREY:
            file += "grey/";
            break;
        case ORANGE:
            file += "orange/";
            break;
        case YELLOW:
            file += "yellow/";
            break;
        default:
            break;
    }
}

void Player::initializeWingImage(WingState wingState) {
    std::string wingType = file + to_string(wingState);
    wings[wingState] = Image(rend, wingType);
}

void Player::initialiceDuckImages(DuckState state , bool walk1 = false) {
    std::string action = file + to_string(state, walk1);
    std::vector<Image> images = {Image(rend, action)};
    ducks[state] = images;
}

Player::Player(SDL_Renderer* rend, Color color): rend(rend), flip(SDL_FLIP_NONE), file("img_src/ducks/"), weaponON(false), walk1(true) {
    
    chooseColor(color);


    // Crea el primer pato y lo agrega al hashmap
    for (int i = STANDING; i <= PLAY_DEAD; i++) {
        DuckState duckState = static_cast<DuckState>(i);
        initialiceDuckImages(duckState);
        if (duckState == WALK) {
            initialiceDuckImages(duckState, true);
        }
    }

    *duck = ducks[STANDING][0];
    
    // Crea el ala normal y la agrega al hashmap
    for (int j = NORMAL; j <= FLAPDOWN; j++){
        WingState wingState = static_cast<WingState>(j);
        initializeWingImage(wingState);
    }

    *wing = wings[NORMAL];

    // -------- QueryTexture --------
    duck->queryTexture();
    wing->queryTexture();
}

void Player::defineSize(int height, int width) {
    duck->defineSize(height, width);
    wing->defineSize(int(15*height/32), int(15*width/32));
    // El tamaño original de los png son del pato 32x32 y del ala 15x15
}

void Player::updateWing(int x, int y) {

    // Actualiza imagen del ala
    if (state == SLOW_FALL) {
        if (flapup) {
            *wing = wings[FLAPUP];
            flapup = false;
        } else {
            *wing = wings[FLAPDOWN];
            flapup = true;
        }
    } else {
        if (weaponON) {
            *wing = wings[HOLD];
        } else {
            *wing = wings[NORMAL];
        }
    }

    // Actualiza posicion del ala
    if (flip = SDL_FLIP_HORIZONTAL) {
        wing->position(x + 1.7*OFFSETX, y);
    } else {
        wing->position(x + OFFSETX, y);
    }

}

void Player::update(int x, int y, DuckState state, Side side) {
    this->state = state;

    // Actualizo la imagen del pato y su posicion
    if ((state == WALK) && (walk1 == false)) {
        *duck = ducks[state][1];
        walk1 = true;
    } else {
        *duck = ducks[state][0];
        walk1 = false;
    }
    
    duck->position(x, y);
    
    if (side == LEFT) {
        flip = SDL_FLIP_HORIZONTAL;
    }

    // Actualizo la image del ala y su posicion
    updateWing(x, y);
}

void Player::fill() {
    // Dinujo el cueerpo dl pato
    duck->fill(flip);

    // Dibujo el arma que tiene el pato
    if (weaponON && (state != SLOW_FALL) && (state != PLAY_DEAD)) {
        //weapon.fill(flip);
    }

    // Dibujo el ala del pato
    if (state != PLAY_DEAD) {
        wing->fill(flip);
    }
}

void Player::weapon() {
    if (weaponON) { // Dropeo
        weaponON = false;
        // Actualizo pos del arma cuando la suelto
        /* y suelto el arma que tenia */
    } else {
        weaponON = true;
        /* me llega y actualizo el arma que tengo*/
    }
}

void Player::shoot() {
    if (!weaponON) {
        return; // Si no tiene unn arma no hace nada
    }

    /*
        Disparo el arma
        Me fijo cuantos usos le quedan
        En caso de quedarse sin usos la dropeo (la mato), weaponON = false y actualizo el alita
        
    */
}
