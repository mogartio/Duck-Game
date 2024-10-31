#include "player.h"

#include <vector>
#include <iostream>

#define OFFSETX 10
#define OFFSETY 13

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
    std::string wingType = file + wingState_to_string(wingState);

    // ------ Opcion 1 -------
    // Image w(rend, wingType);
    // wings.emplace(wingState, std::move(w));

    // ------ Opcion 2 -------
    // wings.insert({wingState, Image(rend, wingType)});

    // ------ Opcion 3 -------
    // std::cout << wingType << std::endl;
    // wings[wingState] = Image(rend, wingType);

    // ------ Opcion 4 ------
    // Image w(rend, wingType);
    // wings.push_back(std::move(w));

    // ------ Opcion 5 ------
    std::vector<Image> images;
    images.emplace_back(rend, wingType);
    wings.emplace(wingState, std::move(images));
}

void Player::initialiceDuckImages(DuckState state) {
    std::string action = file + duckState_to_string(state);
    std::vector<Image> images;
    images.emplace_back(rend, action);
    if (state == DuckState::WALK) {
        action = file + duckState_to_string(state, false);
        images.emplace_back(rend, action);
    }
    ducks.emplace(state, std::move(images));
}


Player::Player(SDL_Renderer* rend, Color color): rend(rend), flip(SDL_FLIP_NONE), file("img_src/ducks/"), weaponON(false), walk1(true) {
    
    chooseColor(color);


    // Crea el primer pato y lo agrega al hashmap
    for (int i = int(DuckState::STANDING); i <= int(DuckState::PLAY_DEAD); i++) {
        DuckState duckState = static_cast<DuckState>(i);
        initialiceDuckImages(duckState);
    }

    duck = &ducks[DuckState::STANDING][0];
    
    // Crea el ala normal y la agrega al hashmap
    for (int j = int(WingState::NORMAL); j <= int(WingState::FLAPDOWN); j++){
        WingState wingState = static_cast<WingState>(j);
        initializeWingImage(wingState);
    }

    wing = &wings[(WingState::NORMAL)][0];

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
    if (state == DuckState::SLOW_FALL) {
        if (flapup) {
            wing = &wings[(WingState::FLAPUP)][0];
            flapup = false;
        } else {
            wing = &wings[(WingState::FLAPDOWN)][0];
            flapup = true;
        }
    } else {
        if (weaponON) {
            wing = &wings[(WingState::HOLD)][0];
        } else {
            wing = &wings[(WingState::NORMAL)][0];
        }
    }

    // Actualiza posicion del ala
    if (flip == SDL_FLIP_HORIZONTAL) {
        wing->position(x + 1.7*OFFSETX, y + OFFSETY);
    } else {
        wing->position(x + OFFSETX, y + OFFSETY);
    }

}

void Player::update(int x, int y, DuckState state, Side side) {
    this->state = state;

    // Actualizo la imagen del pato y su posicion
    if ((state == DuckState::WALK) && (walk1 == false)) {
        duck = &ducks[state][1];
        walk1 = true;
    } else {
        duck = &ducks[state][0];
        walk1 = false;
    }
    
    duck->position(x, y);
    
    if (side == LEFT) {
        flip = SDL_FLIP_HORIZONTAL;
    } else {
        flip = SDL_FLIP_NONE;
    }

    // Actualizo la image del ala y su posicion
    updateWing(x, y);
}

void Player::fill() {
    // Dibujo el cueerpo dl pato
    duck->fill(flip);

    // Dibujo el arma que tiene el pato
    if (weaponON && (state != DuckState::SLOW_FALL) && (state != DuckState::PLAY_DEAD)) {
        //weapon.fill(flip);
    }

    // Dibujo el ala del pato
    if (state != DuckState::PLAY_DEAD) {
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
